#!/bin/bash
make
if [ $# -eq 1 ]
then
	./cnfMaker $1 res.cnf
	minisat res.cnf res.txt
	./solutionReader $1 res.txt
else
	echo ./correctRandom pourcentWall gridWidth
fi
