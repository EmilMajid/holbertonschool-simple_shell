#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"





void set_argv(char *line, char ***argv)
{
	char *line_copy = NULL;
	char *arg;
	unsigned long argc;
	unsigned long i = 0;

	line_copy = strdup(line);

	arg = strtok(line_copy, " \n");
	while (arg != NULL)
	{
		arg = strtok(NULL, " \n");
		argc++;
	}
	free(line_copy);

	*argv = malloc(sizeof(char *) * (argc + 1));
	arg = strtok(line, " \n");
	for (i = 0; i < argc; i++)
	{
		(*argv)[i] = arg;
		arg = strtok(NULL, " \n");
	}
	(*argv)[i] = NULL;
}









int main(void)
{
	char *line = NULL;
	char **argv;
	unsigned long line_len = 0;
	long line_read = 0;
	unsigned int pid;
	int status;

		line_read = getline(&line, &line_len, stdin);
		set_argv(line, &argv);

		for (int i = 0; argv[i] != NULL; i++) {
			printf("%s\n", argv[i]);
		}
	
		/*
		pid = fork();

		if (pid == 0)
		{
			execve(argv[0], argv, NULL);
		}
		else
		{
			wait(&status);
			free(line);
			free(argv);
		}
*/
	return (0);
}
