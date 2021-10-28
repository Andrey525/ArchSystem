#!/bin/bash

rm -rf ./results/*[!.gitkeep]
make clean
make all

./bin/dgemmexe --size 2000
./bin/dgemmOMPexe --size 2000 --count-threads 2
./bin/dgemmOMPexe --size 2000 --count-threads 3
./bin/dgemmOMPexe --size 2000 --count-threads 4
./bin/dgemmPTexe --size 2000 --count-threads 2
./bin/dgemmPTexe --size 2000 --count-threads 3
./bin/dgemmPTexe --size 2000 --count-threads 4
mpiexec -n 2 ./bin/dgemmMPIexe --size 2000 
mpiexec -n 3 ./bin/dgemmMPIexe --size 2000 
mpiexec -n 4 ./bin/dgemmMPIexe --size 2000 

echo "End of program"