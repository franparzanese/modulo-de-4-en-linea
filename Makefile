# Compilador y flags.
CC := gcc
CFLAGS := -std=c17 -Wall -Wextra -Iinclude

# Flags de Criterion (framework de testing).
CRITERION_CFLAGS != pkg-config --cflags criterion
CRITERION_LIBS != pkg-config --libs criterion

# Directorios para los ejecutables y ficheros intermedios.
BIN_FOLDER := bin/
BUILD_FOLDER := build/

# Ejecutables.
MAIN_BIN := $(BIN_FOLDER)modulo4EnLinea
TEST_BIN := $(BIN_FOLDER)tests

# Ficheros intermedios.
MAIN_OBJ := $(BUILD_FOLDER)main.o
SRC_OBJ := $(BUILD_FOLDER)evaluation.o \
	$(BUILD_FOLDER)game.o \
	$(BUILD_FOLDER)grill.o \
	$(BUILD_FOLDER)solver.o
TEST_OBJ := $(BUILD_FOLDER)tests/test_evaluation.o \
	$(BUILD_FOLDER)tests/test_game.o \
	$(BUILD_FOLDER)tests/test_grill.o \
	$(BUILD_FOLDER)tests/test_solver.o

all: $(MAIN_BIN)
	./$<

$(MAIN_BIN): $(MAIN_OBJ) $(SRC_OBJ)
	mkdir -p $(@D)
	$(CC) $^ -o $@

$(BUILD_FOLDER)%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_FOLDER)

fclean: clean
	rm -rf $(BIN_FOLDER)

re: fclean all

test: $(TEST_BIN)
	./$<

$(TEST_BIN): $(SRC_OBJ) $(TEST_OBJ)
	mkdir -p $(@D)
	$(CC) $^ -o $@ $(CRITERION_LIBS)

$(BUILD_FOLDER)tests/%.o: tests/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CRITERION_CFLAGS) -c $< -o $@

.PHONY: all clean fclean re test
