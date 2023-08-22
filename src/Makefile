
IDIR=C:\msys64\mingw64\include
CC=gcc
LDIR=C:\msys64\mingw64\lib
LIBS=-lraylib

CFLAGS=-I$(IDIR) -L$(LDIR)

_DEPS = raylib.h

_OBJ = snake_main.c

all: snake.exe

snake.exe: $(_OBJ)
	@echo "Making snake..."
	$(CC) -o $@ $(_OBJ) $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f ../snake.exe