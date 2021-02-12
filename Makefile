SRC = adventure.c rooms.c items.c characters.c
OBJ = adventure.o rooms.o items.o characters.o
PROG = test

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
