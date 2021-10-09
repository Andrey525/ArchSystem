#!/bin/bash
rm -rf result.csv
printf "MemoryType;BlockSize;ElementType;BufferSize;LaunchNum;Timer;WriteTime(s);ReadTime(s);AverageWriteTime(s);AverageReadTime(s);WriteBandwidth(MB/s);ReadBandwidth(MB/s);AbsError(write);RelError(write);AbsError(read);RelError(read);\n" >> result.csv
cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release
counttests=10
./bin/memtestexe -m RAM -b 64 B -l $counttests
counttests=10
./bin/memtestexe -m HDD -b 4 MB -l $counttests
counttests=10
./bin/memtestexe -m flash -b 4 MB -l $counttests