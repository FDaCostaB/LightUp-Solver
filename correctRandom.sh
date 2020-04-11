#!/bin/bash

if [ $# -eq 2 ]
then
	make
	./gridGeneration $1 $2 res.grid
	./cnfMaker res.grid res.cnf
	minisat res.cnf res.txt > minisat.output
	./solutionReader res.grid res.txt
	./satTo3sat res.cnf 3res.cnf
	minisat 3res.cnf 3res.txt > minisat.output
	./solutionReader res.grid 3res.txt
else
	echo ./correctRandom pourcentWall gridWidth
fi
