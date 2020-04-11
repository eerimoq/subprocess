INC += \
	. \
	../../include \
	$(shell $(NALA) include_dir)
SRC += \
	$(shell $(NALA) c_sources) \
	../../src/subprocess.c \
	main.c
CFLAGS += \
	-Werror \
	-O0 \
	-g \
	-Wall \
	-fprofile-arcs \
	-ftest-coverage \
	-no-pie \
	$(INC:%=-I%)
NALA ?= nala

test:
	$(CC) $(CFLAGS) $(SRC) -o main
	./main

nala_mocks.h: main.c
	[ -f nala_mocks.h ] || touch nala_mocks.h
	$(CC) $(INC:%=-I%) -E main.c | $(NALA) generate_mocks
