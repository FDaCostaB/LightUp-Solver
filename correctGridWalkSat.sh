#!/bin/bash

if [ "$1" = "-help" ]
then
	echo Command use : 	\(2 args - Correct the grid given\) $0 mode grid.txt
	echo 					mode : 1 JW heuristics
	echo 					mode : 2 MOMS heuristics
	echo 					mode : 3 Score heuristics
	echo 					mode : 4 Least modified heuristics
	echo 				\(3 args - Correct a random grid\) : $0 mode pourcentWall gridWidth
else
	if [ $# -eq 2 ]
	then
		make
		./cnfMaker $2 res.cnf
		echo
		echo WalkSat
		./walkSat $1 res.cnf res.txt
		./solutionReader $2 res.txt
	
		./satTo3sat res.cnf 3res.cnf
	
		echo
		echo WalkSat - 3SAT
		./walkSat $1 3res.cnf 3res.txt
		./solutionReader $2 3res.txt
		
		echo
		echo Minisat - 3SAT
		minisat 3res.cnf 3res.txt > minisat.output
		./solutionReader $2 3res.txt
		rm -r res.* 3res.*
	else
		if [ $# -eq 3 ]
		then
			./correctRandomWalkSat $1 $2 $3
		else
			echo Command use 	\(2 args - Correct the grid given\) : $0 mode grid.txt
			echo 				\(3 args - Correct a random grid\) : $0 mode pourcentWall gridWidth
			echo $0 -help for more info.
		fi
	fi
fi
