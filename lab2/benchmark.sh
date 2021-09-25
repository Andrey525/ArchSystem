#!/bin/bash

 printf "PModel;Task;OpType;Opt;InsCount;Timer;Time;LNum;AvTime;AbsErr;RelErr;TaskPerf\n" >> result.csv
 printf "PModel;Task;OpType;Opt;InsCount;Timer;Time;LNum;AvTime;AbsErr;RelErr;TaskPerf" >> result.csv
 
 # make prog-O0
 # ./bin/prog-O0 -counttests 2 -int

 #  make prog-O1
 # ./bin/prog-O1 -counttests 2 -int

 #  make prog-O2
 # ./bin/prog-O2 -counttests 2 -int

 #  make prog-O3
 # ./bin/prog-O3 -counttests 2 -int

