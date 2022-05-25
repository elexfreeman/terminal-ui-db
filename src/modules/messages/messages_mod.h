#ifndef MESSAGE_MOD_H
#define MESSAGE_MOD_H

#include "../../db/messages_db.h"
#include "../../libs/datastd/slice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void messages_input();
void messages_print_list();

char *messages_input_data();
#endif
