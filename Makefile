CC=gcc
CFLAGS=-Wall -Wextra -Wconversion -Wuninitialized -O2
LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl

default: main.o glad.o stb_image.o
	${CC} main.o glad.o stb_image.o -o window.out ${LIBS} && ./window.out

stb_image.o: stb_image.c
	${CC} ${COMPILER_FLAGS} -c stb_image.c

main.o: main.c
	${CC} ${COMPILER_FLAGS} -c main.c

glad.o: glad.c
	${CC} ${COMPILER_FLAGS} -c glad.c

clean:
	rm *.o window.out
