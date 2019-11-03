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
NARMOCK ?= PYTHONPATH=/home/erik/workspace/narmock python3 -m narmock

test:
	$(CC) $(CFLAGS) $(SRC) -o main
	./main

__mocks__.c: main.c
	$(CC) $(CFLAGS) -E main.c | $(NARMOCK) -g
	$(NARMOCK) -f > __mocks__.ld
