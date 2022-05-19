CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncurses

BUILD_DIR=./build/
LINK_DIR=./build/link/

SOURCES=./src/main.c

OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=terminal-ui-db

all: $(SOURCES) $(EXECUTABLE)

	  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)$@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $(LINK_DIR)$@

clean:
	rm -rf $(LINK_DIR)*.o hello
