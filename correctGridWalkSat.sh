#!/bin/bash

if [ $# -eq 1 ]
then
	make
	./cnfMaker $1 res.cnf
	./walkSat res.cnf res.txt
	echo
	echo
	echo WalkSat
	./solutionReader $1 res.txt
	./satTo3sat res.cnf 3res.cnf
	./walkSat 3res.cnf 3res.txt
	echo
	echo
	echo WalkSat - 3SAT
	./solutionReader $1 3res.txt
	echo
	echo
	echo Minisat - 3SAT
	minisat 3res.cnf 3res.txt > minisat.output
	./solutionReader $1 3res.txt
else
	echo ./correctRandom gridFile
fi
