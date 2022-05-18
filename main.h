#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

/* Constants */
#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/* function to run the command */
void lsh_loop(void);
/* Read the command from standard input */
char *lsh_read_line(void);
/* Separate the command string into a program and arguments */
char **lsh_split_line(char *);
/* Run the parsed command */
int lsh_launch(char **);

/* FUnction for builtin shell commands */
int lsh_cd(char **);
int lsh_help(char **);
int lsh_exit(char **);


#endif
