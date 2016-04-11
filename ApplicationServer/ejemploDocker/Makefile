COMP = gcc
FLAGS = -g
TARGET = restful_server.c
OTHERLIB = mongoose.c
OTHERSTUFF = -lpthread -DMG_ENABLE_THREADS
OUT = server


main:
	$(COMP) $(FLAGS) $(TARGET) $(OTHERLIB) $(OTHERSTUFF) -o $(OUT)
	./$(OUT)
