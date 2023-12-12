all: compile run

all_multi: compile_multi run

compile_multi:
	gcc -fopenmp -std=c99 -o ../compiles/main main.c leitura.c utilidade.c knn.c

compile:
	gcc -std=c99 -o ../compiles/main main.c leitura.c utilidade.c knn.c

run:
	../compiles/main