
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

VERBOSE = TRUE

BUILD_DIR=./build/
LINK_DIR=build/link/

BUILD_TESTS_DIR=./build/tests/


EXECUTABLE=terminal-ui-db

OBJECTS=sqlite3.o \
  memory.o slice.o \
  ini.o config.o \
  db.o \
  messages_db.o \
  messages_mod.o \
  list_scr.o \
  main_menu_scr.o \
  router_sys.o \
  terminal_sys.o \
  input_wiget.o

# =============================
# EXECUTABLE FILES
# =============================

MAIN_OBJECTS = $(OBJECTS) main.o

all: $(MAIN_OBJECTS) @(BUILD_DIR)config.ini
	$(info  )
	$(info ======= $@ ========)
	$(CC) -o $(BUILD_DIR)$(EXECUTABLE) $(MAIN_OBJECTS) $(LDFLAGS)
	$(BUILD_DIR)$(EXECUTABLE)

run:
	$(BUILD_DIR)$(EXECUTABLE)


# =============================
# LINKER FILES
# =============================

# main.c
main.o : ./src/main.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/main.c

sqlite3.o : ./src/libs/sqlite3.h ./src/libs/sqlite3ext.h ./src/libs/sqlite3.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/sqlite3.c

ini.o : ./src/libs/ini.c ./src/libs/ini.h
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/ini.c

config.o : ./src/config/config.c ./src/config/config.h
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/config/config.c

memory.o : ./src/libs/datastd/memory.h ./src/libs/datastd/memory.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/datastd/memory.c

slice.o : ./src/libs/datastd/slice.h ./src/libs/datastd/slice.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/libs/datastd/slice.c


# =============================
@(BUILD_DIR)config.ini: config.ini
	$(info ======= $@ ========)
	cat config.ini > ./build/config.ini
# =============================

db.o : ./src/db/db.h ./src/db/db.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/db/db.c

messages_db.o : ./src/db/messages_db.h ./src/db/messages_db.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/db/messages_db.c

# =============================

input_wiget.o : ./src/wigets/input_wiget.h ./src/wigets/input_wiget.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/wigets/input_wiget.c

messages_mod.o : ./src/modules/messages/messages_mod.h ./src/modules/messages/messages_mod.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/modules/messages/messages_mod.c


main_menu_scr.o : ./src/modules/screens/main_menu_scr.h ./src/modules/screens/main_menu_scr.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/modules/screens/main_menu_scr.c 

list_scr.o : ./src/modules/screens/list_scr.h ./src/modules/screens/list_scr.c 
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/modules/screens/list_scr.c


router_sys.o  : ./src/sys/router/router_sys.h ./src/sys/router/router_sys.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/sys/router/router_sys.c

terminal_sys.o  : ./src/sys/terminal/terminal_sys.h ./src/sys/terminal/terminal_sys.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/sys/terminal/terminal_sys.c


# =============================
# TESTS
# =============================

@(BUILD_TESTS_DIR)config.ini: config.ini
	$(info ======= $@ ========)
	cat config.ini > ./build/tests/config.ini

test_messages.o : ./src/tests/test_messages.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/tests/test_messages.c

test_messages_obj = $(OBJECTS) test_messages.o

test_messages: $(test_messages_obj) @(BUILD_TESTS_DIR)config.ini
	$(info  )
	$(info ======= $@ ========)
	$(CC) -o $(BUILD_TESTS_DIR)$@ $(test_messages_obj) $(LDFLAGS)
	$(BUILD_TESTS_DIR)$@

#=============================

test_terminal_view.o : ./src/tests/test_terminal_view.c
	$(info  )
	$(info ======= $@ ========)
	$(CC) -c $(LDFLAGS) ./src/tests/test_terminal_view.c

test_terminal_view_obj = $(OBJECTS) test_terminal_view.o

test_terminal_view: $(test_terminal_view_obj) @(BUILD_TESTS_DIR)config.ini
	$(info  )
	$(info ======= $@ ========)
	$(CC) -o $(BUILD_TESTS_DIR)$@ $(test_terminal_view_obj) $(LDFLAGS)
	$(BUILD_TESTS_DIR)$@

clean:
	rm -rf *.o

