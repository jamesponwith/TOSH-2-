#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include "wrappers.h"

/**
 * Prints out a message if an error has occured
 *
 * @param *msg A message to be displayed to the address
 * the error has that has occured
 */
void unix_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/*
 * Error handling for the fork() function
 */
pid_t Fork(void) {
    pid_t pid = 0;
    if ((pid = fork()) < 0) {
        unix_error("Fork error");
    }
    return pid;
}

/**
 * Handles the child and makes the parent process wait
 * as the child process executes. Additionally, waitpid
 * reaps all children.
 * 
 * @param int sig Attribute unused
 */
void child_handler(__attribute__ ((unused)) int sig) {
    pid_t pid = 0;
    int status;
    while ((pid = waitpid(pid, &status, WNOHANG)) != -1) {}
}

int isNumber(char *number) {
	int i = 0;

	// checking for negative numbers
	if (number[0] == '-') {
		i = 1;
	}
	for (; number[i] !=0; i++) {
		if (!isdigit(number[i])) {
			return 0;
		}
	}
	return 1;
}
