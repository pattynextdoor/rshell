CC = g++
CC_FLAGS = -Wall -ansi
EXEC = rshell
TARGETDIR = bin 
TARGET = $(TARGETDIR)/$(EXEC)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES: .cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
