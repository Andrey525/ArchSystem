all: prog-O0 prog-O1 prog-O2 prog-O3

prog-O0: build/main-O0.o bin
	gcc build/main-O0.o -o bin/prog-O0 -lm

prog-O1: build/main-O1.o bin
	gcc build/main-O1.o -o bin/prog-O1 -lm

prog-O2: build/main-O2.o bin
	gcc build/main-O2.o -o bin/prog-O2 -lm

prog-O3: build/main-O3.o bin
	gcc build/main-O3.o -o bin/prog-O3 -lm	

build/main-O0.o: src/main.c build
	gcc -Wall -Werror -O0 -c src/main.c -o build/main-O0.o

build/main-O1.o: src/main.c build
	gcc -Wall -Werror -O1 -c src/main.c -o build/main-O1.o

build/main-O2.o: src/main.c build
	gcc -Wall -Werror -O2 -c src/main.c -o build/main-O2.o

build/main-O3.o: src/main.c build
	gcc -Wall -Werror -O3 -c src/main.c -o build/main-O3.o

build:
	mkdir build
bin: 
	mkdir bin

clean:
	rm -rf bin build

.PHONY: clean