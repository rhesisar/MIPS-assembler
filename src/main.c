// Projet MIPS 2022-2023
// Auteurs: GUIGUET_HOLDEN

#include <stdio.h>
#include <string.h>
#include "modes.h"

int main(int argc, char **argv)
{
	switch (argc){
	case 1:
		if (interMode()){
			fprintf(stderr, "Error occurred during interactive mode\n");
			return 1;
		}
		printf("Interactive mode exited successfully\n");
		return 0;
	case 3:
		if (!strcmp(argv[2], "-pas")){
			if (stepMode(argv[1])){
				printf("Error occurred during step-by-step mode\n");
				return 1;
			}
			printf("Step-by-step mode exited successfully\n");
			return 0;
		}
		return 1;
	case 4:
		if (autoMode(argv[1], argv[2], argv[3])){
			printf("Error occurred during automatic mode\n");
			return 1;	
		}
		printf("Automatic mode exited successfully\n");
		return 0;
	}
    return 0; /* NOTREACHED */
}
