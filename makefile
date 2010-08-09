.PHONY= doc clean

CC=g++
OPTIONS= -g -Wall -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -DDEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= images.o actor.o Teclado.o control_animacion.o imagen.o animacion.o map.o irrXML.o camera.o heroe.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

.PHONY: all clean doc test

all: main

main: ./src/main.cc $(OBJ)
	$(CC) $(OPTIONS) -I$(INCLUDEDIR) ./src/main.cc $(OBJ) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cc $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) -c -I$(INCLUDEDIR) -o $@ $<

doc:
	doxygen

clean:
	rm -f $(OBJ)
	rm -f main
