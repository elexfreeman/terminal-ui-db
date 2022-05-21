
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


BUILD_DIR=./build/out/
LINK_DIR=./build/link/

BUILD_TESTS_DIR=./build/tests/ 

DATA_STD=./src/libs/datastd/memory.h ./src/libs/datastd/memory.c \
  ./src/libs/datastd/slice.h ./src/libs/datastd/slice.c

SQLITE=./src/libs/sqlite3.h \
  ./src/libs/sqlite3ext.h \
  ./src/libs/sqlite3.c

INIT_LIB=./src/libs/ini.h ./src/libs/ini.c

CONFIG_LIB=./src/config/config.h \
  ./src/config/config.c \
  ./src/libs/ini.h \
  ./src/libs/ini.c

# =============================
# SRC

SOURCES=./src/main.c \
  ./src/wigets/table_wiget.c \
  ./src/wigets/input_wiget.c \
  $(CONFIG_LIB) \
  $(SQLITE) \
  $(DATA_STD)

SRC_TEST_MESSAGES=./src/tests/test_messages.c \
  $(CONFIG_LIB) \

# =============================
# OBJECTS

OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=terminal-ui-db

# $(info $(SOURCES:.c=.o))

# =============================

all: $(SOURCES) $(EXECUTABLE)



init.o : ./src/libs/ini.c ./src/libs/ini.h
	$(CC) -c $(LDFLAGS) ./src/libs/ini.c -o $(LINK_DIR)$@

config.o : ./src/config/config.c ./src/config/config.h
	$(CC) -c $(LDFLAGS) ./src/config/config.c -o $(LINK_DIR)$@


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)$@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $(LINK_DIR)$@


# =============================
#

test_messages.o : ./src/tests/test_messages.c
	$(CC) -c $(LDFLAGS) ./src/tests/test_messages.c -o $(LINK_DIR)$@


test_messages_obj = test_messages.o init.o config.o

test_messages: $(test_messages_obj)
	$(CC) -o $(BUILD_TESTS_DIR)$@ $(addprefix $(LINK_DIR),$(test_messages_obj)) $(LDFLAGS)


clean:
	rm -rf $(LINK_DIR)*.o $(BUILD_DIR)* $(BUILD_TESTS_DIR)*
