all: dgemmexe dgemmMPIexe dgemmOMPexe dgemmPTexe

# Начало сборки последовательной программы
dgemmexe: build/main.o lib/libdgemm.a 
	gcc build/main.o -L./lib -ldgemm -o bin/dgemmexe

lib/libdgemm.a: build/dgemm.o 
	ar rc lib/libdgemm.a build/dgemm.o

build/dgemm.o: src/dgemm/dgemm.c src/dgemm/dgemm.h
	gcc -Wall -Werror -c src/dgemm/dgemm.c -o build/dgemm.o

build/main.o: src/main/main.c src/dgemm/dgemm.h
	gcc -Wall -Werror -c src/main/main.c -o build/main.o
# Конец сборки последовательной программы

# Начало сборки Posix-threads программы
dgemmPTexe: build/mainPT.o lib/libdgemmPT.a
	gcc build/mainPT.o -L./lib -ldgemmPT -o bin/dgemmPTexe -lpthread

lib/libdgemmPT.a: build/dgemmPT.o 
	ar rc lib/libdgemmPT.a build/dgemmPT.o

build/dgemmPT.o: src/dgemm/dgemmPT.c src/dgemm/dgemmPT.h
	gcc -Wall -c src/dgemm/dgemmPT.c -o build/dgemmPT.o

build/mainPT.o: src/main/mainPT.c src/dgemm/dgemmPT.h
	gcc -Wall -c src/main/mainPT.c -o build/mainPT.o
# Конец сборки Posix-threads программы

# Начало сборки параллельной OMP программы
dgemmOMPexe: build/mainOMP.o lib/libdgemmOMP.a
	gcc build/mainOMP.o -L./lib -ldgemmOMP -o bin/dgemmOMPexe -fopenmp

lib/libdgemmOMP.a: build/dgemmOMP.o 
	ar rc lib/libdgemmOMP.a build/dgemmOMP.o

build/dgemmOMP.o: src/dgemm/dgemmOMP.c src/dgemm/dgemmOMP.h
	gcc -Wall -Werror -c src/dgemm/dgemmOMP.c -o build/dgemmOMP.o -fopenmp

build/mainOMP.o: src/main/mainOMP.c src/dgemm/dgemmOMP.h
	gcc -Wall -Werror -c src/main/mainOMP.c -o build/mainOMP.o
# Конец сборки параллельной OMP программы

# Начало сборки параллельной MPI программы
dgemmMPIexe: build/mainMPI.o lib/libdgemmMPI.a
	mpicc build/mainMPI.o -L./lib -ldgemmMPI -o bin/dgemmMPIexe

lib/libdgemmMPI.a: build/dgemmMPI.o 
	ar rc lib/libdgemmMPI.a build/dgemmMPI.o

build/dgemmMPI.o: src/dgemm/dgemmMPI.c src/dgemm/dgemmMPI.h
	mpicc -Wall -Werror -c src/dgemm/dgemmMPI.c -o build/dgemmMPI.o

build/mainMPI.o: src/main/mainMPI.c src/dgemm/dgemmMPI.h
	mpicc -Wall -Werror -c src/main/mainMPI.c -o build/mainMPI.o
# Конец сборки параллельной MPI программы

clean:
	rm -rf bin/*[!.gitkeep] build/*[!.gitkeep] lib/*[!.gitkeep]

.PHONY: clean