#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

int main(void)
{
	char *line = NULL;
	char *line_copy = NULL;
	char **argv;
	char *arg;
	unsigned long line_len = 0;
	long line_read = 0;
	unsigned long argc = 0;
	unsigned long i = 0;
	unsigned int pid;
	int status;

	while (1)
	{
		line_read = getline(&line, &line_len, stdin);
		if (line_read == -1)
		{
			break;
		}

		line_copy = strdup(line);
		arg = strtok(line_copy, " \n");
		while (arg != NULL)
		{
			arg = strtok(NULL, " \n");
			argc++;
		}
		free(line_copy);

		argv = malloc(sizeof(char *) * (argc + 1));
		arg = strtok(line, " \n");
		for (i = 0; i < argc; i++)
		{
			argv[i] = arg;
			arg = strtok(NULL, " \n");
		}
		argv[argc] = NULL;

		pid = fork();

		if (pid == 0)
		{
			execve(argv[0], argv, environ);
		}
		else
		{
			wait(&status);
		}

	}
	return (0);
}
