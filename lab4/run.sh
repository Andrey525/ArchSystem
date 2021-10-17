rm ./results/* ./cachegrind/*

cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release

for var in {1..10}
    do
    let size="$var*1000"
    let block_size="$var*100"
    # valgrind --tool=cachegrind --cachegrind-out-file=./cachegrind/cachegrind.out.$var ./bin/dgemmexe --size $size --block-size $block_size
    ./bin/dgemmexe --size $size --block-size $block_size
    done