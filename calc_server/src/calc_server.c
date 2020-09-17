#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <errno.h>
#include <sys/neutrino.h>

// server side define for math operation
#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY 'x'
#define DIVIDE '/'

int main (int argc, char* argv[])
{
	int rcvid;         // indicates who we should reply to
	int chid;          // the channel ID
	char message [50]; // big enough for our purposes
	char op = ' ';
	int val1 = 0;
	int val2 = 0;
	int totalVal = 0;
	char *reply;

	// create a channel
	chid = ChannelCreate (0);
	if (chid == -1)
	{
		perror("failed to create the channel.");
		exit (EXIT_FAILURE);
	}
	printf("Server PID is %d\n", getpid());
	// this is typical of a server:  it runs forever
	while (1) {
		// get the message, and print it
		rcvid = MsgReceive (chid, message, sizeof (message), NULL);

		sscanf(message, "%d,%c,%d", &val1, &op, &val2 );

		printf("Server: %d %c %d",val1, op, val2);

		printf("Server message.");

		switch(op) {
		case ADD:
			totalVal = val1 + val2;
			itoa(totalVal, message, 10);
			break;
		case SUBTRACT:
			totalVal = val1 - val2;
			itoa(totalVal, message, 10);
			break;
		case MULTIPLY:
			totalVal = val1 * val2;
			itoa(totalVal, message, 10);
			break;
		case DIVIDE:
			if(val2 != 0) {
				totalVal = val1 / val2;
		        itoa(totalVal, message, 10);
			} else
				strcpy (message, "Cannot divide by 0!");
			break;
		}

		MsgReply (rcvid, EOK, message, sizeof (message));
	}

	// destroy the channel when done
	ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
