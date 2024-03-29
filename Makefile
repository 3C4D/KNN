SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE_KPPV := $(BIN_DIR)/kppv
EXE_GEN  := $(BIN_DIR)/generation_test
EXE_BENCH  := $(BIN_DIR)/benchmark
ALL_EXE  := $(EXE_KPPV) $(EXE_GEN) $(EXE_BENCH)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_GEN  := $(filter-out %main_kppv.o, $(filter-out %benchmark.o, $(OBJ)))
OBJ_KPPV := $(filter-out %generation.o, $(filter-out %benchmark.o, $(OBJ)))
OBJ_BENCH := $(filter-out %main_kppv.o, $(filter-out %main_generation.o, $(OBJ)))

CC := gcc
CPPFLAGS := -Iinc -MMD -MP
CFLAGS   := -Wall -pedantic -g -O2 `pkg-config --cflags MLV`
LDFLAGS  := `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS   := -lm `pkg-config --libs-only-l MLV`

.PHONY: all clean

all: $(ALL_EXE)

$(EXE_GEN): $(OBJ_GEN) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(EXE_KPPV): $(OBJ_KPPV) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(EXE_BENCH): $(OBJ_BENCH) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)

clean_all:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
