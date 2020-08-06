INC = include/
SRC = src/
BIN = bin/
EXE = lray
CFLAGS = -Wall -ansi -O2
XML_PARSER_FLAGS = `xml2-config --cflags` `xml2-config --libs`
G3X_INC = -I./include $(incG3X)
G3X_LIB = $(libG3X)

ALL_SRC = $(shell ls src/)

OBJ = $(patsubst %.c, $(BIN)%.o, $(ALL_SRC))

GENERATOR_OBJ = $(patsubst %.c, $(BIN)%.o, Hmat.c Vecteur.c Point.c Color.c)

all:
	make $(EXE)

$(EXE): $(OBJ)
	gcc $(OBJ) $(CFLAGS) $(XML_PARSER_FLAGS) $(G3X_LIB) -lm -o $@
	cp $(EXE) $(BIN)$(EXE)

$(BIN)Scene.o: $(SRC)Scene.c
	gcc -c $< $(CFLAGS) -lm -o $@
	
$(BIN)Sphere.o: $(SRC)Sphere.c
	gcc -c $< $(CFLAGS) -lm -o $@
	
$(BIN)Vecteur.o: $(SRC)Vecteur.c
	gcc -c $< $(CFLAGS) -lm -o $@
	
$(BIN)Point.o: $(SRC)Point.c
	gcc -c $< $(CFLAGS) -lm -o $@
	
$(BIN)Hmat.o: $(SRC)Hmat.c
	gcc -c $< $(CFLAGS) -lm -o $@
	
$(BIN)Color.o: $(SRC)Color.c
	gcc -c $< $(CFLAGS) -lm -o $@
	
$(BIN)%.o : $(SRC)%.c
	gcc -c $< $(CFLAGS) -o $@
	
$(BIN)Parser.o : $(SRC)Parser.c
	gcc -c $< $(CFLAGS) $(XML_PARSER_FLAGS) -o $@

$(BIN)Window.o : $(SRC)Window.c
	gcc -c $< $(CFLAGS) $(XML_PARSER_FLAGS) $(G3X_INC) -o $@
	
$(BIN)main.o : $(SRC)main.c
	gcc -c $< $(CFLAGS) $(XML_PARSER_FLAGS) $(G3X_INC) -o $@

#$(BIN)Scene_generator.o : $(SRC)Scene_generator.c
#	gcc -c $< $(CFLAGS) -o $@

generator: $(GENERATOR_OBJ) Scene_generator.c
	gcc $^ $(CFLAGS) -lm -o $(BIN)$@
	
clean:
	rm -f bin/*.o
	rm -f bin/*
	rm -f $(EXE)
