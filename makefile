CC=g++
CC_FLAGS =-Wall -Werror -ansi -pedantic
TARGET = ./bin/rshell
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES: .cpp=.o)

all:
	mkdir -p ./$(TARGETDIR)
	$(CC) $(CC_FLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf ./$(TARGETDIR)
