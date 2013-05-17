#compiler
CC=g++
CFLAGS=-c -Wall -pedantic -std=c++11
LIBS=-lsfml-system -lsfml-window -lsfml-graphics
SRC=Main.cpp GameObject.cpp GameObjectFactory.cpp Player.cpp BasicEnemy.cpp Utils.cpp Collision.cpp
OBJ=$(SRC:.cpp=.o)
OUT=SFMLTest

all: $(SRC) $(OUT)

$(OUT): $(OBJ)
	$(CC) $(LIBS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(OUT)
