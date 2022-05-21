
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

BUILD_TESTS_DIR=./build/tests/


EXECUTABLE=terminal-ui-db

# $(info $(SOURCES:.c=.o))

# =============================
#
MAIN_OBJECTS = $(OBJECTS) main.o

all: $(MAIN_OBJECTS)
	$(info  )
	$(info ======= $@ ========)
	$(CC) -o $(BUILD)$(EXECUTABLE) $(addprefix $(LINK_DIR),$(test_messages_obj)) $(LDFLAGS)
	$(BUILD_DIR)$(EXECUTABLE)

main.o : ./src/main.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/main.c -o $(LINK_DIR)$@



sqlite3.o : ./src/libs/sqlite3.h ./src/libs/sqlite3ext.h ./src/libs/sqlite3.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/sqlite3.c -o $(LINK_DIR)$@

init.o : ./src/libs/ini.c ./src/libs/ini.h
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/ini.c -o $(LINK_DIR)$@

config.o : ./src/config/config.c ./src/config/config.h
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/config/config.c -o $(LINK_DIR)$@

memory.o : ./src/libs/datastd/memory.h ./src/libs/datastd/memory.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/datastd/memory.c -o $(LINK_DIR)$@

slice.o : ./src/libs/datastd/slice.h ./src/libs/datastd/slice.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/datastd/slice.c -o $(LINK_DIR)$@


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)$@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $(LINK_DIR)$@


# =============================
#

test_messages.o : ./src/tests/test_messages.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/tests/test_messages.c -o $(LINK_DIR)$@


test_messages_obj = test_messages.o init.o config.o

test_messages: $(test_messages_obj)
	$(info  )
	$(info ======= $@ ========)
	$(CC) -o $(BUILD_TESTS_DIR)$@ $(addprefix $(LINK_DIR),$(test_messages_obj)) $(LDFLAGS)
	$(BUILD_TESTS_DIR)$@


clean:
	rm -rf $(LINK_DIR)*.o
