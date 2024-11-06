#
# Makefile
#

CC = clang
LD = clang

CFLAGS = -std=c17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS = -framework OpenGL -lglfw -lm

SRC = $(shell find src -name '*.c')
OBJ = $(SRC:.c=.o)
OUT = ./out

.PHONY: all clean
all: $(OUT)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUT): $(OBJ)
	$(LD) -o $@ $< $(LDFLAGS)

clean:
	rm -fr $(OUT)
	rm -fr $(OBJ)

