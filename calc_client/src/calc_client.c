#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>

// server side define for math operation
#define ADD "+"
#define SUBTRACT "-"
#define MULTIPLY "x"
#define DIVIDE "/"

/**
 * Msg_Passing_Client.c
 *
 * Usage: ./Msg_Passing_Client PID_of_Server
 *
 * Edit the Launch Configuration for the client (gear icon) > Arguments tab > enter PID of server
 */
int main (int argc, char* argv[])
{

	// malloc string length of each argv to char pointer (string variable)
	char *smsg = NULL;
	int val1 = 0;
	int val2 = 0;
	int isValid = 1;

	printf("argc: %d\n", argc);
	// there can only be 5 arguments in this program ... the program name, PID, val1, operator, and val2
	if(argc == 5) {

		if(atoi(argv[2]) != 0 || atoi(argv[4]) != 0) {

			if(strcmp(argv[3], "+") == 0 || strcmp(argv[3], "-") == 0 || strcmp(argv[3], "x") == 0 || strcmp(argv[3], "/") == 0) {

				smsg = malloc(strlen(argv[2]) + strlen(",") + strlen(argv[3]) + strlen(",") + strlen(argv[4]) + 1);

				// append values to smsg in client side
				strcpy(smsg, argv[2]);
				strcat(smsg, ",");
				strcat(smsg, argv[3]);
				strcat(smsg, ",");
				strcat(smsg, argv[4]);
				char rmsg [200];
				int  coid;
				pid_t serverpid = atoi(argv[1]);

				// pulled out values from 1 string for server side ensure int
				if(strcmp(argv[3], ADD) == 0)
					sscanf(smsg, "%d,+,%d", &val1, &val2 );
				else if(strcmp(argv[3], SUBTRACT) == 0)
					sscanf(smsg, "%d,-,%d", &val1, &val2 );
				else if(strcmp(argv[3], MULTIPLY) == 0)
					sscanf(smsg, "%d,x,%d", &val1, &val2 );
				else if(strcmp(argv[3], DIVIDE) == 0)
					sscanf(smsg, "%d,/,%d", &val1, &val2 );

				printf("Client: %d and %d\n", val1, val2);

				// establish a connection
				coid = ConnectAttach (ND_LOCAL_NODE, serverpid, 1, _NTO_SIDE_CHANNEL, 0);
				if (coid == -1) {
					fprintf (stderr, "Couldn't ConnectAttach\n");
					perror (NULL);
					exit (EXIT_FAILURE);
				}
				// send the message
				if (MsgSend (coid, smsg, strlen (smsg) + 1, rmsg, sizeof (rmsg)) == -1) {
					fprintf (stderr, "Error during MsgSend\n");
					perror (NULL);
					exit (EXIT_FAILURE);
				}

				if (strlen (rmsg) > 0) {
					printf ("The server returns \"%s\"\n", rmsg);
				}


				//Disconnect from the channel
				ConnectDetach(coid);


				free(smsg);
			} else {
				printf("Invalid operator %s", argv[3]);
			}
		} else
			printf("Argument is not a number.");
	} else
		printf("Invalid number of arguments.");

	return EXIT_SUCCESS;
}
