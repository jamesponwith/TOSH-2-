/*
 * The Tiny Torero Shell (TTSH)
 *
 * This class sets up a data structure to
 * represent a circular queue which will 
 * be used to store the history of commands.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "history_queue.h"

static HistoryEntry history[MAXHIST]; 

static int front = 0;
static int rear = 0;
static int cmd_count = 0;

/*
 * Enables the '!num' syntax to execute
 * a command by the command number
 *
 * @ret 0 if command not in history
 * @ret 1 if command is in history
 */
//TODO: switch to int, return 1 if add to history
int numToCmd(char *cmd) {
	printf("cmd = %s\n", cmd);
	if (strcmp(cmd, "latest") == 0) {
		memset(cmd, 0, MAXLINE);
		strcpy(cmd, history[rear - 1].cmdline);
		printf("null thingy worked");
		return 1;
	}
	unsigned int cmd_index = atoi(cmd);
	for (int i = 0; i < MAXHIST; i++) { 
		if (cmd_index == history[i].cmd_num) {
			strcpy(cmd, history[i].cmdline);
			return 1;
		}
	}
	return 0;
}

/*
 * Copies the users most recent command
 * into the circular queue while 
 * assiging each with a command number
 */
void addEntry(char new_cmd[MAXLINE]) {
	cmd_count++;

	strcpy(history[rear].cmdline, new_cmd);
	history[rear].cmd_num = cmd_count;

	rear = (rear + 1) % MAXHIST;

	if (cmd_count > MAXHIST) {
		front = (front + 1) % MAXHIST;				
	}
}

/*
 * Loops through the history queue printing
 * the most recent 10 commands
 */
void printHistory(int num_to_print) {
	int j = front + num_to_print;
	/*int j = front - MAXHIST + num_to_print;*/
	if (num_to_print > MAXHIST || num_to_print < 0) {
		num_to_print = MAXHIST;
	}
	/*int j = MAXHIST - num_to_print + 2;*/
	/*int i = MAXHIST - num_to_print; */
	for (int i = 0; i < num_to_print; i++) { // loop through num_to_print number of times
		if (strcmp("", history[j].cmdline) != 0) {
			fprintf(stdout, "%u\t%s\n", history[j].cmd_num, history[j].cmdline);
		}
		j++;
		if (j == MAXHIST) {
			j = 0;
		}
	}
}
