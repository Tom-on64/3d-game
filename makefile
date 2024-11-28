CC = clang
LD = clang

CFLAGS = -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS = -lSDL2

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
OUT = ./out

.PHONY: all clean

all: $(OUT)
$(OUT): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -f $(OBJ)
	rm -f $(OUT)

