/*
 * The Not-So-Tiny Torero Shell (TOSH)
 *
 * Add your top-level comments here.
 */

#define _XOPEN_SOURCE 600

#include <ctype.h>
#include <libgen.h>
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>


// TODO: add your function prototypes here as necessary

pid_t Fork(void);
void unix_error(char *msg);
void execCmd(char *argv[], int ret);
void child_handler(__attribute__ ((unused)) int sig); 

int main(){ 

	
	// TODO: add a call to signal to register your signal handler on 
	//       SIGCHLD here
	

	struct sigaction sa;
	sa.sa_handler = child_handler;
	sa.sa_flags = SA_NOCLDSTOP;
	sigaction(SIGCHLD, &sa, NULL);


	while(1) {
		// (1) read in the next command entered by the user
		char *cmdline = readline("tosh$ ");

		// NULL indicates EOF was reached, which in this case means someone
		// probably typed in CTRL-d
		if (cmdline == NULL) {
			fflush(stdout);
			exit(0);
		}

		fprintf(stdout, "DEBUG: %s\n", cmdline);

		// TODO: complete the following top-level steps
		// (2) parse the cmdline

		// (3) determine how to execute it, and then execute it

	}

	return 0;
}


/**
 * Prints out a message if an error has occured
 *
 * @param *msg A message to be displayed to address
 * the error that has occured
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
 * Execute commands in argv
 * @param argv Command line arguments
 * @param ret Determines if command to run in the foreground
 * or background
 */
void execCmd(char *argv[], int ret) {
	int status;
	pid_t child_pid;
	if((child_pid = Fork()) == 0) {
		setpgid(0,0);
		if(execv(argv[0], argv) == -1) {
			fprintf(stdout, "ERROR: command not found\n");
			exit(0);
		}
	}
	else if {
		waitpid(child_pid, &status, 0); // Wait for child
	}
}



/*
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
