#!/bin/bash

for grid in $@
do
  echo -----------------------JW-----------------------
  ./correctGridWalkSat.sh 1 $grid
  echo ----------------------MOMS----------------------
  ./correctGridWalkSat.sh 2 $grid
  echo ---------------------SCORE----------------------
  ./correctGridWalkSat.sh 3 $grid
  echo -----------------LEAST MODIFIED-----------------
  ./correctGridWalkSat.sh 4 $grid
done
