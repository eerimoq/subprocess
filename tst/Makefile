CFLAGS ?= \
	-Werror \
	-O3 \
	-g \
	-Wall

test:
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage \
	    -I../include narwhal.c ../src/subprocess.c main.c -o main
	./main
