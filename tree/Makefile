CC = gcc
IN = tree
OUT = $(IN)
BUILD = ./build/
SRC = ./src/$(IN).c
BIN = $(BUILD)$(OUT)
VIZ = output

$(BIN): $(SRC)
	$(CC) -Wall -Wextra -o $@ $<

.PHONY: run clean debug plot open
run: $(BIN)
	$<

check_memory: $(SRC)
	$(CC) -Wall -Wextra -fsanitize=address -o $(BUILD)$(OUT)_check_memory $<
	$(BUILD)$(OUT)_check_memory

clean: $(BUILD)
	rm $<*
	rm *.png
	rm *.dot

debug: $(SRC)
	$(CC) -Wall -Wextra -ggdb -o $(BUILD)$(OUT)_debug $<
	gdb --tui $(BIN)_debug

plot:
	dot -Tpng $(VIZ).dot -o $(VIZ).png

open:
	xdg-open $(VIZ).png
