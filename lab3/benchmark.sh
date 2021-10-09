#!/bin/bash
rm -rf result.csv
printf "MemoryType;BlockSize(MB);ElementType;BufferSize(MB);LaunchNum;Timer;WriteTime(s);ReadTime(s);AverageWriteTime(s);WriteBandwidth(MB/s);AbsError(write);RelError(write);AverageReadTime(s);ReadBandwidth(MB/s);AbsError(read);RelError(read);\n" >> result.csv
cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release
counttests=3
./bin/memtestexe -m HDD -b 4 MB -l $counttests

AverageWriteTime=$(bc <<< "scale=6; $(sed 's/;/\t/g' result.csv | cut -f 7 | tail -n $counttests | tr "\012" "+" ; echo "0")")
AverageWriteTime=$(bc <<< "scale=6; $AverageWriteTime/$counttests")
AverageWriteTime=$(echo $AverageWriteTime | sed -e 's/^/0/')
echo $AverageWriteTime
printf "$AverageWriteTime;" >> result.csv

WriteBandwidth=$(bc <<< "scale=6; $(sed 's/;/\t/g' result.csv | cut -f 2 | tail -n $counttests | tr "\012" "+" ; echo "0")")
WriteBandwidth=$(bc <<< "$WriteBandwidth/$counttests/$AverageWriteTime")
printf "$WriteBandwidth;" >> result.csv
