# YATE (Yet Another Text-based Esolang)

YATE is an esolang, or esoteric programming language, that uses single-character commands and is almost entirely made of letters.

## Numbers
Numbers in YATE:

- Aren't of a fixed length; instead, the interpreter reads digits until it finds a hyphen.
- Are written in octal and reverse.
- Are written using letters, using a specific letter-to-number system:

	- For the first digit, 0 is R, 1 is S, 2 is L, 3 is U, 4 is N, 5 is B, 6 is E, and 7 is Z.
	- The digits for the second digit are the same as the first one, except shifted left four spaces. Note that the digits roll over, so the second digit's numbers are N, B, E, Z, R, S, L, & U.
- Are negative if they begin with a hyphen.
If a number contains a V, the variable named after the letter following the V will be added to the number. This feature allows, for example, to print the value of a variable plus one without modifying the variable.

## Strings
Strings are started with a quotation mark and ended with a hyphen. 

## Variables
Variables in YATE are named after a lowercase letter of the alphabet.

There are four types of variables:

- Number variables;
- Array variables, that require allocating memory for them to use;
- File variables;

At the start of the program, the O and I variables are defined, corresponding to standard output and standard input respectively.

## Errors
### Illegal Command
This error occurs the program tries to use a command that's not on the command cheat sheet.

### Undefined Function
This error occurs when the program tries to call a function that has not been defined.

## Commands
### Parameters

- If a parameter's name starts with "d", it only accepts a variable name.
- If a parameter's value begins with a V, the V will be followed by a variable name.
- If a parameter's name is "s" or "arr", it is a string terminated by a hyphen.

### Command List

#### Arithmetic

- `a<y><dx>`: Add y to dx.
- `s<y><dx>`: Subtract y from dx.
- `m<y><dx>`: Multiply dx by y.
- `d<y><dx>`: Divide dx by y.

#### Pointers and Arrays

- `b`: Unused.
- `h<i><n><arr>`: Set the ith element of arr to n.
- `i<arr><n><d>`: Set d to the nth element of arr.
- `p<e><dp>`: Set dp to a pointer in memory to e.

#### I/O
- `o<f><p>`: Open the file with path p into f*.
- `r<n><f><d>`: Read n bytes from f to array d.
- `n<f><n>`: Read a number from f to n.
- `w<f><s>`: Write s to f.
- `z<f><n>`: Write number n to f.
- `u<f><n>`: Write ASCII character number n to f.
- `c<r><g><b>`: Set the console color.

#### Conditions
- `e<x><y>(...)[(...)]`: If x is equal to y, execute the 1st block of code; else, execute the 2nd block of code.
- `g<x><y>(...)[(...)]`: If x is greater than y, execute the 1st block of code; else, execute the 2nd block of code.
- `l<x><y>(...)[(...)]`: If x is less than y, execute the 1st block of code; else, execute the 2nd block of code.

#### Setting values
- `f<d>(...)`: Define function d.
- `v<s><d>`: Set variable d to s.
- `y<d>`: Set d to a random 24-bit integer.

#### Control Flow
- `j<n>`: Jump to relative position n.
- `k<n>`: Jump to absolute position n.
- `q<n>`: Call function n.

#### Misc.
- `t<d>`: Set d to the current UNIX epoch.
- `x<inst><params>`: Use an extended instruction.

*If P is I or O, it gets replaced with either stdin or stdout.

### Extended instruction set

- `xo<y><dx>`: Bitwise OR dx by y.
- `xa<y><dx>`: Bitwise AND dx by y.
- `xx<y><dx>`: Bitwise XOR dx by y.
- `xc<y><dx>`: Compress list y into list dx.
- `xd<y><dx>`: Decompress list y into list dx.
- `xg<url><darr>`: Set darr to the response of a GET request to url.
- `xs<d><darr>`: Split darr every d.

## Examples

### Hello, World!

```
wo"Hello, World!-.
```

### Cat program

```
rs-iawoakn-.
```
Note: This program doesn't need a period (since it's in an infinite loop), but i placed the period just for consistency.

### Truth Machine

```
nieee-(zoe jb-)(zoe).
```

