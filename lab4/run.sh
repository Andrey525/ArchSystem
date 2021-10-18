rm ./results/* ./cachegrind/*

cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release

for var in {1..4}
    do
    let size="2**($var + 10 - 1)"
    let block_size="2**($var + 8)"
    # echo "$size"
    # echo "$block_size"
    # valgrind --tool=cachegrind --cachegrind-out-file=./cachegrind/cachegrind.out.$var ./bin/dgemmexe --size $size --block-size $block_size
    ./bin/dgemmexe --size $size --block-size $block_size
    done