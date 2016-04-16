SOURCE=$(wildcard src/*.cpp)
LIBS=$(wildcard mongoose-master/*.c)
FLAGS=-lpthread -DMG_ENABLE_THREADS
all:
	g++ $(LIBS) $(SOURCE) -o main $(FLAGS)
