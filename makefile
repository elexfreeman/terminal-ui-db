CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11
LDFLAGS=-std=c11 -Wextra -pedantic -lncursesw
BUILD_DIR=./build/
LINK_DIR=./build/link/

SOURCES=./src/main.c \
  ./src/wigets/table_wiget.c \
  ./src/wigets/input_wiget.c

OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=terminal-ui-db

all: $(SOURCES) $(EXECUTABLE)

	  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)$@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $(LINK_DIR)$@

clean:
	rm -rf $(LINK_DIR)*.o hello
