#!/bin/bash

rm -rf result.csv info.txt

count=10

# printf "PModel;Task;OpType;Opt;InsCount;Timer;Time;LNum;AvTime;AbsErr;RelErr;TaskPerf\n" >> result.csv
printf "PModel;Task;OpType;Opt;Timer;Time;LNum;AvTime;AbsErr;RelErr\n" >> result.csv

make prog-O0
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "0\n" >> info.txt
./bin/prog-O0 -counttests $count -int
./bin/prog-O0 -counttests $count -float
./bin/prog-O0 -counttests $count -double
rm -rf info.txt

make prog-O1
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "1\n" >> info.txt
./bin/prog-O1 -counttests $count -int
./bin/prog-O1 -counttests $count -float
./bin/prog-O1 -counttests $count -double
rm -rf info.txt

make prog-O2
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "2\n" >> info.txt
./bin/prog-O2 -counttests $count -int
./bin/prog-O2 -counttests $count -float
./bin/prog-O2 -counttests $count -double
rm -rf info.txt

make prog-O3
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "3\n" >> info.txt
./bin/prog-O3 -counttests $count -int
./bin/prog-O3 -counttests $count -float
./bin/prog-O3 -counttests $count -double
rm -rf info.txt


# for ((i = 0; i < count; i++))
# do
# lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> result.csv
# done

