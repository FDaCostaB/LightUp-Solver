EXECUTABLES = testOfFunctions cnfMaker solutionReader gridGeneration satTo3sat

all : $(EXECUTABLES)

testOfFunctions : generation.o main.o grid.o logic.o dimacs.o
	clang -g -Wall $^ -o $@

satTo3sat : generation.o satTo3sat.o grid.o logic.o dimacs.o
	clang -g -Wall $^ -o $@

cnfMaker : generation.o cnfMaker.o grid.o logic.o dimacs.o
	clang -g -Wall $^ -o $@

solutionReader : generation.o solutionReader.o grid.o logic.o dimacs.o
	clang -g -Wall $^ -o $@

gridGeneration : generation.o gridGeneration.o grid.o logic.o dimacs.o
	clang -g -Wall $^ -o $@

gridGeneration.o : gridGeneration.c
	clang -g -c -Wall gridGeneration.c

solutionReader.o : solutionReader.c
	clang -g -c -Wall solutionReader.c

satTo3sat.o : satTo3sat.c
	clang -g -c -Wall satTo3sat.c

cnfMaker.o : cnfMaker.c
	clang -g -c -Wall cnfMaker.c

generation.o : generation.c generation.h
	clang -g -c -Wall generation.c

grid.o : grid.c grid.h
	clang -g -c -Wall grid.c

logic.o : logic.c logic.h
	clang -g -c -Wall logic.c

dimacs.o : dimacs.c dimacs.h
	clang -g -c -Wall dimacs.c

main.o : main.c
	clang -g -c -Wall main.c

clean:
	rm -r *.o testOfFunctions cnfMaker solutionReader