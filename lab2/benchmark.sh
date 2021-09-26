#!/bin/bash

rm -rf result.csv info.txt

count=3

printf "PModel;Task;OpType;Opt;Timer;Time;LNum;AvTime;AbsErr;RelErr;InsCount;TaskPerf\n" >> result.csv

make prog-O0
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "0\n" >> info.txt

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O0 -counttests $count -int
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O0 -counttests $count -float
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O0 -counttests $count -double
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
# instr=$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')
# time=$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

rm -rf info.txt

make prog-O1
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "1\n" >> info.txt

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O1 -counttests $count -int
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O1 -counttests $count -float
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O1 -counttests $count -double
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

rm -rf info.txt

make prog-O2
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
printf "2\n" >> info.txt

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O2 -counttests $count -int
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O2 -counttests $count -float
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./bin/prog-O2 -counttests $count -double
instr=$(bc <<< "$(callgrind_annotate callgrind.out | grep dgemv | tr --delete , | awk '{print $1}')/$count")
taskperf=$(bc <<< "$instr/$(sed 's/;/\t/g' result.csv | cut -f 8 | tail -n 1)")
printf "$instr;" >> result.csv
printf "$taskperf;\n" >> result.csv

rm -rf info.txt

# make prog-O3
# lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> info.txt
# printf "3\n" >> info.txt
# ./bin/prog-O3 -counttests $count -int
# ./bin/prog-O3 -counttests $count -float
# ./bin/prog-O3 -counttests $count -double
# rm -rf info.txt


# for ((i = 0; i < count; i++))
# do
# lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0}' >> result.csv
# done

