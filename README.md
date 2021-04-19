# INF432
A translation of any instances of 'Ligth Up' puzzle problem in Conjunctive normal form. With a random switching SAT-Solver coded in C. https://en.wikipedia.org/wiki/Light_Up_(puzzle)

correctGrid.sh : Correct a grid file with minisat (SAT problem and his 3SAT reduction) and disp
the correction.
Command line : ./correctRandom <grid>

correctRandom.sh : Correct a random grid generated with parameters given with minisat (SAT
problem and his 3SAT reduction) and disp the correction.
Command line : ./correctRandom <percentWall> <gridWidth>

correctGridWalkSat.sh : Correct a (random) grid with the WalkSat (SAT problem and his 3SAT
reduction) and minisat (3SAT reduction) to compare and disp the correction of solutions given.
Command line : (2 args - Correct the grid given) ./correctGridWalkSat.sh <mode> <grid>
(3 args - Correct a random grid) : ./correctGridWalkSat.sh <mode> <percentWall> <gridWidth>
mode :  1 JW heuristics
        2 MOMS heuristics
        3 Score heuristics
        4 Least modified heuristics

correctRandomWalkSat.sh : Called by correctGridWalkSat.sh and do the same work with a random
grid.
Command line : See above.

correctAllGridGiven.sh : Call correctGridWalkSat.sh with all grid file given as arguments. (Uses
for test)

The format used for the grid file begin with the size S of the grid followed by S line of S character where
a character represent a box. The character used for the different box are the following :
\# : Empty wall 0,1,2,3,4 : Numbered walls : Free case

Exemple:
6
\_\_\_0\#\_
\_\#\_\_\_\_
1\_\_\_3\_
#\_\_\_1\_
\_3\_\_\_\_
\_\_\_\#\#\_
