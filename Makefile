CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/graph.o $(OBJ)/heap.o $(OBJ)/main.o
HDRS = $(INC)/graph.h $(INC)/heap.h
CFLAGS = -g -Wall -c -I$(INC)

EXE = $(BIN)/tp2.out

# Garante que os diretórios existem
#DIRS = $(OBJ) $(BIN)

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $(DIRS)

$(BIN)/tp2.out: $(OBJS)
	$(CC) -g -o $(BIN)/tp2.out $(OBJS) $(LIBS)

$(OBJ)/graph.o: $(HDRS) $(SRC)/graph.c
	$(CC) $(CFLAGS) -o $(OBJ)/graph.o $(SRC)/graph.c

$(OBJ)/heap.o: $(HDRS) $(SRC)/heap.c
	$(CC) $(CFLAGS) -o $(OBJ)/heap.o $(SRC)/heap.c

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c

clean:
	rm -f $(EXE) $(OBJS) gmon.out
