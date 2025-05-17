CC = gcc
IN = linked
OUT = $(IN)
BUILD = ./build/
SRC = ./src/$(IN).c
BIN = $(BUILD)$(OUT)

$(BIN): $(SRC)
	$(CC) -Wall -Wextra -o $@ $<

.PHONY: run clean debug
run: $(BIN)
	$<

check_memory: $(SRC)
	$(CC) -Wall -Wextra -fsanitize=address -o $(BUILD)$(OUT)_check_memory $<
	$(BUILD)$(OUT)_check_memory

clean: $(BUILD)
	rm $<*

debug: $(SRC)
	$(CC) -Wall -Wextra -ggdb -o $(BUILD)$(OUT)_debug $<
	gdb --tui $(BIN)_debug

