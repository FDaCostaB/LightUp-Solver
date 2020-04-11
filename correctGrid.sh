#!/bin/bash

if [ $# -eq 1 ]
then
	make
	./cnfMaker $1 res.cnf
	minisat res.cnf res.txt > minisat.output
	./solutionReader $1 res.txt
	./satTo3sat res.cnf 3res.cnf
	minisat 3res.cnf 3res.txt > minisat.output
	./solutionReader $1 3res.txt
else
	echo ./correctRandom gridFile
fi
