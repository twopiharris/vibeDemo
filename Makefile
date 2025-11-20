CC = gcc
CFLAGS = -O2 -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
SRC = src/main.c
BIN = bin/game

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -rf bin

.PHONY: all clean
