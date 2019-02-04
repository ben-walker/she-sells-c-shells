EXE = tusk

SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LEX = $(SRC_DIR)/parser.lex
LEX_C = $(SRC_DIR)/lex.yy.c
LEX_O = $(OBJ_DIR)/lex.yy.o
FLEX = flex --outfile=$(LEX_C)

CPPFLAGS += -Iinclude
CFLAGS += -Wall -pedantic -std=c99 -D_SVID_SOURCE -D_XOPEN_SOURCE=700
LDFLAGS += $()
LDLIBS += $()

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) $(LEX_O)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(RM) $(LEX_C)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LEX_C): $(LEX)
	$(FLEX) $<

clean:
	$(RM) $(OBJ) $(EXE) $(LEX_C)
