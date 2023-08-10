COMPILER=gcc
COMPILER_FLAGS=-Wall -Wextra -Wconversion -Wuninitialized
LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl

default: main.o glad.o
	${COMPILER} main.o glad.o -o window.out ${LIBS} && ./window.out

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} -c main.c

glad.o: glad.c
	${COMPILER} ${COMPILER_FLAGS} -c glad.c

build: main.o glad.o
	${COMPILER} main.o glad.o -o window.out ${LIBS}

clean:
	rm *.o window.out
