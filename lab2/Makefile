bin/prog: build/main.o bin
	gcc build/main.o -o bin/prog -lm

build/main.o: src/main.c build
	gcc -Wall -Werror -c src/main.c -o build/main.o

build:
	mkdir build
bin: 
	mkdir bin

clean:
	rm -rf bin build

.PHONY: clean