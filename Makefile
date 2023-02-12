all:
	make -B yate
	make test

yate:
	gcc -g main.c -o yate

test:
	./yate truthmachine.yate
