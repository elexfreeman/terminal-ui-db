#ifndef MESSAGE_MOD_C
#define MESSAGE_MOD_C

#include "./messages_mod.h"
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h>  /* for wait */
#include <unistd.h>

void messages_print_list(int offset, int limit) {
  Slice *list = message_list(offset, limit);

  fprintf(stdout, "\r\n");
  for (int i = 0; i < Slice_Size(list); i++) {
    fprintf(stdout, "-------------------------------------------\r\n");
    t_message_item *item = Slice_Get(list, i);
    fprintf(stdout, "ID: %d\r\n", item->id);
    fprintf(stdout, "%ls", item->msg);
  }

  fprintf(stdout, "\r\n");
  fprintf(stdout, "\r\n");
  message_free_slice(list);
}

char *messages_input_data() {

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  remove("./msg.txt");
  /*Spawn a child to run the program.*/
  pid_t pid = fork();
  if (pid == 0) { /* child process */
    static char *argv[] = {"nvim", "./msg.txt", NULL};
    execv("/bin/nvim", argv);
    exit(127);          /* only if execv fails */
  } else {              /* pid!=0; parent process */
    waitpid(pid, 0, 0); /* wait for child to exit */
  }

  fp = fopen("./msg.txt", "r");
  if (fp == NULL) {
    fclose(fp);
    return NULL;
  }

  char *msg = malloc(sizeof(char *));
  char *tmp = NULL;
  size_t msg_Len = 0;
  int i = 1;
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t len_p_dst = len * sizeof(char *);
    if (i == 1) {
      tmp = malloc(len_p_dst);
      sprintf(tmp, "%s", line);
    } else {
      tmp = malloc(msg_Len + len_p_dst);
      sprintf(tmp, "%s%s", msg, line);
    }

    free(msg);
    msg = malloc(msg_Len + len_p_dst);
    sprintf(msg, "%s", tmp);
    free(tmp);
    i++;
  }

  fclose(fp);

  return msg;
}

void messages_input() {
  char *line = messages_input_data();
  if (line) {
    fprintf(stdout, "->>%s", line);
    message_add(line);
    free(line);
  }
}

#endif
