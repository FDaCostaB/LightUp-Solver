#!/bin/bash

INDEX=0

if [ $# -eq 3 ]
	then
	make
	./cnfMaker $2 res.cnf
	rm $3
	touch $3
	while [ $INDEX -ne 1000 ]
	do
		echo $INDEX
		./walkSat $1 res.cnf res.txt >> $3
		INDEX=$((INDEX+1))
		sleep 1
	done
fi
