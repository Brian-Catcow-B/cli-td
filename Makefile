CC = gcc
CFLAGS = -Wall -Wextra -g

PROJECT = cliTD

SRC = src
OBJ = objects
BIN = bin

OBJ_FILES = $(OBJ)/game.o $(OBJ)/board.o $(OBJ)/enemy.o $(OBJ)/data_structures.o $(OBJ)/log.o $(OBJ)/window.o $(OBJ)/pos2d.o $(OBJ)/tower.o
LIBS = -lncurses

all: mkdirs $(PROJECT)

$(PROJECT): $(OBJ_FILES) $(OBJ)/main.o
	$(CC) -o $(PROJECT) $^ $(LIBS)
	mv $(PROJECT) $(BIN)/

mkdirs:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $^
	mv *.o $(OBJ)/

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $^
	mv main.o $(OBJ)/

clean:
	rm -rf $(OBJ)/* $(BIN)/* $(SRC)/*.gch logs.txt
