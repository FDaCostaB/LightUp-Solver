main : generation.o main.o
	clang -Wall $^ -o $@
	
generation.o : generation.c generation.h
	clang -c -Wall generation.c

main.o : main.c
	clang -c -Wall main.c