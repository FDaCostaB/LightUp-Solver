#!/bin/bash

if [ $# -eq 2 ]
then
	make
	./gridGeneration $1 $2 res.grid
	./cnfMaker res.grid res.cnf
	./walkSat res.cnf res.txt
	echo
	echo
	echo WalkSat
	./solutionReader res.grid res.txt
	./satTo3sat res.cnf 3res.cnf
	echo
	echo
	echo WalkSat - 3SAT
	./walkSat 3res.cnf 3res.txt
	./solutionReader res.grid 3res.txt
	echo
	echo
	echo Minisat - 3SAT
	minisat 3res.cnf 3res.txt > minisat.output
	./solutionReader res.grid 3res.txt
else
	echo ./correctRandom pourcentWall gridWidth
fi
