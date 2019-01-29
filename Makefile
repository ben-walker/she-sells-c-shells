EXE = tusk

SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LEX_C = $(SRC_DIR)/lex.yy.c
LEX_O = $(OBJ_DIR)/lex.yy.o
LEX = $(SRC_DIR)/parser.lex

CPPFLAGS += -Iinclude
CFLAGS += -Wall -pedantic -std=c99
LDFLAGS += $()
LDLIBS += $()

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) $(LEX_O)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LEX_C): $(LEX)
	flex --outfile=$@ $<

clean:
	$(RM) $(OBJ) $(EXE) $(LEX_C)
