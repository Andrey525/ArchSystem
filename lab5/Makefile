all: dgemmexe 

dgemmexe: build/main.o lib/libdgemm.a 
	gcc build/main.o -L./lib -ldgemm -o bin/dgemmexe -lm

lib/libdgemm.a: build/dgemm.o src/dgemm/dgemm.h
	ar rc lib/libdgemm.a build/dgemm.o

build/dgemm.o: src/dgemm/dgemm.c
	gcc -Wall -Werror -c src/dgemm/dgemm.c -o build/dgemm.o

build/main.o: src/main/main.c
	gcc -Wall -Werror -c src/main/main.c -o build/main.o

# dgemmMPIexe: build/mainMPI.o
# 	gcc build/mainMPI.o -o bin/dgemmMPIexe -lm



# build/mainMPI.o: src/main.c
# gcc -Wall -Werror -c src/mainMPI.c -o build/mainMPI.o


clean:
	rm -rf bin/*[!.gitkeep] build/*[!.gitkeep] lib/*[!.gitkeep]

.PHONY: clean