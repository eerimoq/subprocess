INC += \
	. \
	../../include \
	..
SRC += \
	../narwhal.c \
	../../src/subprocess.c \
	main.c
CFLAGS += \
	-Werror \
	-O0 \
	-g \
	-Wall \
	-fprofile-arcs \
	-ftest-coverage \
	$(INC:%=-I%)

test:
	$(CC) $(CFLAGS) $(SRC) -o main
	./main

__mocks__.c: main.c
	$(CC) $(CFLAGS) -E main.c | narmock -g
	narmock -f > __mocks__.ld
