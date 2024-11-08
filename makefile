#
# Makefile
#

CC = clang
LD = clang

CFLAGS = -std=c17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS = -lsdl2

SRC = $(shell find src -name '*.c')
OBJ = $(SRC:.c=.o)
OUT = ./out

.PHONY: all clean
all: $(OUT)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUT): $(OBJ)
	$(LD) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -fr $(OUT)
	rm -fr $(OBJ)

