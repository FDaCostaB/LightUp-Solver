#!/bin/bash

INDEX=0

if [ $# -eq 3 ]
	then
	make
	./cnfMaker $2 res.cnf
	./satTo3sat res.cnf 3res.cnf
	rm $3
	touch $3
	while [ $INDEX -ne 1000 ]
	do
		echo $INDEX
		./walkSat $1 3res.cnf 3res.txt >> $3
		INDEX=$((INDEX+1))
		sleep 1
	done
fi
