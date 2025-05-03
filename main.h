#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;
int fork_and_execute(char **argv)
char **string_to_words_array(char *line, int *status)
char *search_path_for_command(char *command, int *status)
char *get_path(void)

#endif
