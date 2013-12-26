#compiler
CC=clang++
CFLAGS= -Wall -pedantic -std=c++11
LIBS=-lsfml-system -lsfml-window -lsfml-graphics
SRC=Main.cpp GameObject.cpp GameObjectFactory.cpp Player.cpp BasicEnemy.cpp Block.cpp Utils.cpp TextureManager.cpp
LVLSRC=LevelEditor.cpp GameObject.cpp GameObjectFactory.cpp Player.cpp BasicEnemy.cpp Block.cpp Utils.cpp TextureManager.cpp
OBJ=$(SRC:.cpp=.o)
OUT=SFMLTest
LVLOUT=LevelEditor


all: $(SRC) $(OUT) $(LVLOUT)

$(OUT): $(OBJ)
	$(CC) $(LIBS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(OUT) $(LVLOUT)


$(LVLOUT):
	$(CC) $(CFLAGS) $(LVLSRC) -o $@ $(LIBS)
