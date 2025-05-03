#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "main.h"

/**
 * get_path - returns the PATH
 *
 * Return: the path
 */
char *get_path(void)
{
	char **env = environ;
	char *path = NULL;

	if (env == NULL)
		return (NULL);
	while (*env != NULL)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
			return (path);
		}
		env++;
	}
	return (NULL);
}

/**
 * search_path_for_command - Searches for the full path of a command
 * in directories listed in $PATH.
 * @command: The command to search for.
 * @status: The status code that is updated if the command is not found.
 *
 * Return: The full path to the command if found, or NULL if not found.
 *         If the command is already a full path, it is returned as is.
 */
char *search_path_for_command(char *command, int *status)
{
	char *path = NULL;
	char *path_copy = NULL;
	char *dir = NULL;
	char *full_path = NULL;

	if (command == NULL)
		return (NULL);

	if (strlen(command) == 0)
		return (NULL);

	if (access(command, F_OK) == 0 &&
		(command[0] == '/' || command[1] == '/' || command[2] == '/'))
	{
		full_path = strdup(command);
		return (full_path);
	}
	path = get_path();
	if (path == NULL)
	{
		*status = 127, fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return (NULL);
	}
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		strcpy(full_path, dir), strcat(full_path, "/"), strcat(full_path, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path), dir = strtok(NULL, ":");
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", command);
	*status = 127;
	free(path_copy);
	return (NUL);
}
/**
 * fork_and_execute - Creates a child process and executes a command
 * @argv: Array of command arguments
 *
 * Return: Exit status of the command executed.
 */
int fork_and_execute(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		status = execve(argv[0], argv, environ);
	}
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (status);
}

/**
 * string_to_words_array - Splits a string into an array of words.
 * @line: The string to split into words.
 * @status: The status code that is updated if the last word is "exit".
 *
 * Return: An array of strings (words) from the input string, or NULL
 *         if the string contains no words.
 *         The array is NULL-terminated.
 */
char **string_to_words_array(char *line, int *status)
{
	char *line_copy = NULL;
	char **argv = NULL;
	char *arg = NULL;
	size_t argc = 0;
	size_t i = 0;

	line_copy = strdup(line);
	arg = strtok(line_copy, " \n");
	while (arg)
	{
		argc++;
		arg = strtok(NULL, " \n");
	}
	free(line_copy);

	if (argc == 0)
	{

        argv[i] = NULL;

        if (strcmp(argv[i - 1], "exit") == 0)
                *status = 2;

        (void)status;
        return (argv);
}

/**
 * main - the main function
 *
 * Return: exit status
 */
int main(void)
{
        char *line = NULL;
        char **argv = NULL;
        size_t buffer_length = 0;
        ssize_t input_length = 0;
        int status = 0;


        argv[i] = NULL;

        if (strcmp(argv[i - 1], "exit") == 0)
                *status = 2;

        (void)status;
        return (argv);
}

/**
 * main - the main function
 *
 * Return: exit status
 */
int main(void)
{
        char *line = NULL;
        char **argv = NULL;
        size_t buffer_length = 0;
        ssize_t input_length = 0;
        int status = 0;

        while (1)
        {
                line = NULL;
                argv = NULL;
                input_length = getline(&line, &buffer_length, stdin);
                if (input_length == -1)
                {
                        free(line);
                        break;
                }
                argv = string_to_words_array(line, &status);
                if (argv == NULL)
                {
                        free(argv), free(line);
                        continue;
                }
                if (strcmp(argv[0], "exit") == 0)
                {
                        free(argv), free(line);
                        break;
                }
                argv[0] = search_path_for_command(argv[0], &status);
                if (argv[0] == NULL)
                {
                        free(argv), free(line);
                        continue;
                }

                status = fork_and_execute(argv);
                free(argv[0]), free(argv), free(line);
        }
        exit(status);
}        while (1)
        {
                line = NULL;
                argv = NULL;
                input_length = getline(&line, &buffer_length, stdin);
                if (input_length == -1)
                {
                        free(line);
                        break;
                }
                argv = string_to_words_array(line, &status);
                if (argv == NULL)
                {
                        free(argv), free(line);
                        continue;
                }
                if (strcmp(argv[0], "exit") == 0)
                {
                        free(argv), free(line);
                        break;
                }
                argv[0] = search_path_for_command(argv[0], &status);
                if (argv[0] == NULL)
                {
                        free(argv), free(line);
                        continue;
                }

                status = fork_and_execute(argv);
                free(argv[0]), free(argv), free(line);
        }
        exit(status);
}		return (NULL);
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	arg = strtok(line, " \n");
	for (i = 0; i < argc; i++)
	{
		*(argv + i) = arg;
		arg = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	if (strcmp(argv[i - 1], "exit") == 0)
		*status = 2;

	(void)status;
	return (argv);
}

/**
 * main - the main function
 *
 * Return: exit status
 */
int main(void)
{
	char *line = NULL;
	char **argv = NULL;
	size_t buffer_length = 0;
	ssize_t input_length = 0;
	int status = 0;

	while (1)
	{
		line = NULL;
		argv = NULL;
		input_length = getline(&line, &buffer_length, stdin);
		if (input_length == -1)
		{
			free(line);
			break;
		}
		argv = string_to_words_array(line, &status);
		if (argv == NULL)
		{
			free(argv), free(line);
			continue;
		}
		if (strcmp(argv[0], "exit") == 0)
		{
			free(argv), free(line);
			break;
		}
		argv[0] = search_path_for_command(argv[0], &status);
		if (argv[0] == NULL)
		{
			free(argv), free(line);
			continue;
		}

		status = fork_and_execute(argv);
		free(argv[0]), free(argv), free(line);
	}
	exit(status);
}
