#!/bin/bash
make
if [ $# -eq 2 ]
then
	./gridGeneration $1 $2 res.grid
	./cnfMaker res.grid res.cnf
	minisat res.cnf res.txt
	./solutionReader res.grid res.txt
else
	echo ./correctRandom pourcentWall gridWidth
fi
