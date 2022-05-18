#include "main.h"

/**
 * main - Check the code
 *
 * @argc: argument count
 * @argv: arguments vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	/* Load config files, if any */

	/* Run command loop */
	lsh_loop();

	/* Perform any shutdown/cleanup */

	return (EXIT_SUCCESS);
}

/**
 * lsh_loop - function that handles a command
 *
 * Return: void
 */
void lsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
	} while (status);
}

/**
 * lsh_read_line - read the entry user
 *
 * Return: a string
 */
char *lsh_read_line(void)
{
	int bufsize = LSH_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	/* If the memory allocation didn't work, error */
	if (!buffer)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		/* Read a character */
		c = getchar();

		/* If we hit EOF, replace it with a null character and return */
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		/* If we have exceeded the buffer, reallocate */
		if (position >= bufsize)
		{
			bufsize += LSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * lsh_split_line - parse the input user into a list of arguments
 * @line: the user input
 *
 * Return: the user input or command line
 */
char **lsh_split_line(char *line)
{
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
			{
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * lsh_launch - launch shell processing
 * @args: arguments
 *
 * Return: 1 if the process succeeded, -1 otherwise
 */
int lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
			perror("lsh");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (pid < 0)
		{
			/* Error forking */
			perror("lsh");
		}
		else
		{
			/* Parent process */
			do {
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return (1);
}


/* List of builtin commands, followed by their corresponding functions */
char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[]) (char **) = {&lsh_cd, &lsh_help, &lsh_exit};

/**
 * lsh_num_builtins - count the number of builtin-commands
 *
 * Return: the total length of builtin-commands
 */
int lsh_num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
}

/**
 * lsh_cd - builtin function cd
 * @args: arguments
 * Return: 1 if there are more than 1 argument
 */
int lsh_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "Error: Expected argument to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("lsh");
	}
}

/**
 * lsh_help - builtin function help
 * @args: arguments
 * Return: 1 if there is help manual of the command
 */
int lsh_help(char **args)
{
	int i;
	
	printf("The following are built in:\n");

	for (i = 0; i < lsh_num_builtins(); i++)
		printf("%s\n", builtin_str[i]);

	return (1);
}

/**
 * lsh_exit - builtin function for command exit
 * @args: arguments
 * Return: Always 0
 */
int lsh_exit(char **args)
{
	return (0);
}


/**
 * lsh_execute - launch a builtin command
 * @args: arguments
 * Return: 1 if the command has been executed
 */
int lsh_execute(char **args)
{
	int i;

	if (args[0] == NULL)
		return (1);

	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
	}

	return (lsh_launch(args));
}
