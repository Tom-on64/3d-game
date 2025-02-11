CC = cc
LD = cc

CCFLAGS = -Wall -Wextra -Wpedantic -std=c99
LDFLAGS =

SRC = ./src
BIN = ./bin
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(SRCS))
OUT = ./bin/game

.PHONY: all clean run

all: $(OUT)
$(OUT): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -fr $(OUT) $(OBJS) $(BIN)

run: $(OUT)
	$(OUT)

