CFLAGS += $(shell cat __mocks__.ld)
SRC += \
	__mocks__.c \
	mock_libc.c \
	mock.c

test: __mocks__.c

include ../suite.mk
