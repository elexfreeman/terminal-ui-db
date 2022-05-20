CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11
LDFLAGS= -lncursesw \
  -pthread \
  -DSQLITE_ENABLE_RTREE \
  -DSQLITE_ENABLE_FTS4 \
  -DSQLITE_ENABLE_FTS5 \
  -DSQLITE_ENABLE_JSON1 \
  -DSQLITE_ENABLE_RBU \
  -DSQLITE_ENABLE_STAT4 \
  -lpthread -ldl -lm


BUILD_DIR=./build/
LINK_DIR=./build/link/

SOURCES=./src/main.c \
  ./src/wigets/table_wiget.c \
  ./src/wigets/input_wiget.c \
  ./src/config/config.h \
  ./src/config/config.c \
  ./src/libs/sqlite3.h \
  ./src/libs/sqlite3ext.h \
  ./src/libs/sqlite3.c \
  ./src/libs/ini.h \
  ./src/libs/ini.c

OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=terminal-ui-db

all: $(SOURCES) $(EXECUTABLE)

	  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)$@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $(LINK_DIR)$@

clean:
	rm -rf $(LINK_DIR)*.o hello
