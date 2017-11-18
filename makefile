CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic -std=c++11
TARGET = ./bin/rshell
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES: .cpp=.o)

all:
	mkdir -p bin 
	$(CC) $(CC_FLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf ./$(TARGETDIR)
