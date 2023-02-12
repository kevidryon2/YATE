/* main.c
 *
 * Copyright 2023 kevidryon2
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */



#include <stdlib.h>
#include <stdio.h>

int p(int a, int b) {
	int oa = a;
	b--;
	if (!b) return 1;
	while (b>1) {
		a *= oa;
		b--;
	}
	return a;
};

char program[65536];
int pc = 0;

int nvars[26];
FILE *fvars[26];
int *lvars[26];
int pvars[26];

int readOctalNum() {
	pc++;
	int i = 1;
	int n = 0;
	int sign = 1;
	if (program[pc] == '-') {
		sign = -1;
		pc++;
	}
	while (program[pc] != '-') {
		switch (program[pc]) {
			case 'r': n += 0*p(8,i); break;
			case 's': n += 1*p(8,i); break;
			case 'l': n += 2*p(8,i); break;
			case 'u': n += 3*p(8,i); break;
			case 'n': n += 4*p(8,i); break;
			case 'b': n += 5*p(8,i); break;
			case 'e': n += 6*p(8,i); break;
			case 'z': n += 7*p(8,i); break;
			case 'v':
				pc++;
				n += nvars[program[pc]];
				break;
			default: printf("Invalid number at %d\n", pc); exit(127);
		}
		pc++;
		i++;
	}
	return n*sign;
}

FILE *getReadFile() {
	pc++;
	switch (program[pc]) {
		case 'o':
			return stdout;
			break;
		case 'i':
			return stdin;
			break;
		default:
		 	return fvars[program[pc]-'a'];
			break;
	}
}

void writeToReadVariable(int value) {
	pc++;
	char v = (program[pc]>='A'&program[pc]<='Z')?
				program[pc]+('a'-'A'):
				program[pc];
	nvars[v-'a'] = value;
}

char *readStr() {
	pc++;
	char *s = (char*)calloc(65536,sizeof(char));
	int i;
	if (program[pc] == '"') {
		pc++;
		while (program[pc] != '-') {
			s[i] = program[pc];
			pc++;
			i++;
		}
	} else {
		char v = program[pc];
		return lvars[v-'a'];
	}
	s[i] = 0;
	return s;
}

void nextInst() {
	char inst = (program[pc]>='A'&program[pc]<='Z')?
				program[pc]+('a'-'A'):
				program[pc];
	int x, y;
	char v;
	char *s;
	FILE *f;
	switch (inst) {
		case 'a':
			x = readOctalNum();
			writeToReadVariable(x);
			break;
		case 'c':
			printf("\033[38;2;%d;%d;%dm",
				   readOctalNum(),
				   readOctalNum(),
				   readOctalNum()); //ANSI Escape Code
			break;
		case 'w':
			f = getReadFile();
			s = readStr();
			fwrite(s, 1, 65536, f);
			break;
		case 'z':
			f = getReadFile();
			x = readOctalNum();
			fprintf(f, "%d ", x);
			break;
		case 'u':
			f = getReadFile();
			x = readOctalNum();
			fprintf(f, "%c", x);
			break;
		case 'k':
			pc = x-1;
			break;
		case 'j':
			pc += x-1;
			break;
		case 'n':
			f = getReadFile();
			pc++;
			fscanf(f, "%d", &nvars[program[pc]-'a']);
			break;
		case 'o':
			s = readStr();
			fvars[program[pc]-'a'] = fopen(s, "r");
		case ' ':
		case '\n':
			break;
		case '.': exit(0);
		default:
			printf("Undefined instruction at %d (%c).\n", pc+1, program[pc]);
	}
	pc++;
}

int main(int argc, char **argv) {
	if (argc<2) {
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		printf("Can't open %s\n", argv[1]);
		return 1;
	}
	int plen = fread(program, 1, 65536, fp);
	while (1) {
		if (pc>plen-1) {printf("PC went out of bounds!\n"); exit(127);}
		nextInst();
	}
}
