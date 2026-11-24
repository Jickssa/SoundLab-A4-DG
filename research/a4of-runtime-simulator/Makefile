CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic -Werror
CPPFLAGS += -Iinclude
SRC = src/sim_bus.c src/panel_latch.c src/event.c src/param.c src/scheduler.c
TEST = build/test_runtime

.PHONY: all test clean
all: test

build:
	mkdir -p build

$(TEST): $(SRC) tests/test_runtime.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) tests/test_runtime.c -o $@

test: $(TEST)
	./$(TEST)

clean:
	rm -rf build
