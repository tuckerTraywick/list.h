CC := gcc
CFLAGS := -O1 -g3 -std=c99 -Wall -Wextra -Wpedantic
INCLUDE := -Iinclude

binary/test: build/test.o build/list.o
	@mkdir -p binary
	@$(CC) $(CFLAGS) $^ -o $@

build/%.o: source/%.c
	@mkdir -p build
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

source/test.c: include/list.h

source/list.c: include/list.h

"include/list.h":

.PHONY: clean
clean:
	@rm -rf build binary
