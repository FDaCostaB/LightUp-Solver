#!/bin/bash

if [ "$1" = "-help" ]
then
	echo NEVER USE ./correctRandomWalkSat IT SHOULD BE CALLED BY ./correctGridWalkSat for more convenience
	echo Command use : 	\(2 args - Correct the grid given\) ./correctGridWalkSat mode grid.txt
	echo 					mode : 1 JW heuristics
	echo 					mode : 2 MOMS heuristics
	echo 					mode : 3 Score heuristics
	echo 					mode : 4 Least modified heuristics
	echo 				\(3 args - Correct a random grid\) : ./correctGridWalkSat mode pourcentWall gridWidth
else
	if [ $# -eq 3 ]
	then
		make
		./gridGeneration $2 $3 res.grid
		./cnfMaker res.grid res.cnf
		./walkSat $1 res.cnf res.txt
		echo
		echo
		echo WalkSat
		./solutionReader res.grid res.txt
		./satTo3sat res.cnf 3res.cnf
		echo
		echo
		echo WalkSat - 3SAT
		./walkSat $1 3res.cnf 3res.txt
		./solutionReader res.grid 3res.txt
		echo
		echo
		echo Minisat - 3SAT
		minisat 3res.cnf 3res.txt > minisat.output
		./solutionReader res.grid 3res.txt
		rm -r res.* 3res.*
	else
		echo NEVER USE ./correctRandomWalkSat IT SHOULD BE CALLED BY ./correctGridWalkSat for more convenience
		echo Command use 	\(2 args - Correct the grid given\) : ./correctGridWalkSat mode grid.txt
		echo 				\(3 args - Correct a random grid\) : ./correctGridWalkSat mode pourcentWall gridWidth
		echo $0 -help for more info.
	fi
fi
