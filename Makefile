COMPILER=gcc
COMPILER_FLAGS=-Wall -Wextra -Wconversion -Wuninitialized -O2
LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl

default: main.o glad.o stb_image.o
	${COMPILER} main.o glad.o stb_image.o -o window.out ${LIBS} && ./window.out

build: main.o glad.o stb_image.o
	${COMPILER} main.o glad.o stb_image.o -o window.out ${LIBS}
	
stb_image.o: stb_image.c
	${COMPILER} ${COMPILER_FLAGS} -c stb_image.c

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} -c main.c

glad.o: glad.c
	${COMPILER} ${COMPILER_FLAGS} -c glad.c

clean:
	rm *.o window.out
