/*
 * io.h
 * @brief Input/Output functions
 * @author D.Doty
*/

/* Includes */
#include "io.h"


/* Defines */


/* Global Variables */


/* Private Function Prototypes */

/* For reference:
struct io
{
	uint8_t command;
	uint32_t arg1;
	uint32_t arg2;
};
*/

/* Function Definition */
struct io io_get()
{
	// Define io_get so we can dump out nulls at any error later
	struct io output = {0, 0, 0};

	// Declare and take in input
	char input[MAX_INPUT_LENGTH];
	fgets(input, MAX_INPUT_LENGTH, stdin);

	// Check for problems
	uint8_t length = strlen(input);
	if(length >= MAX_INPUT_LENGTH - 1)
	{
		printf("Error, your command was too long to be valid. Type 'help' for help\r\n");
		return output;
	}

	// Split the input
	//this is kinda shitty for the moment, need to clean up
	
	// uint8_t i = 0;
	// while(input[i] != 0x20)
	// {
	// 	command[i] = input[i];
	// 	i++;
	// }
	// while(input[i] = 0x20)
	// {
	// 	i++;
	// }
	// while(input[i] != 0x20)
	// {
	// 	arg1[i] = input[i];
	// 	i++;
	// }
	// while(input[i] = 0x20)
	// {
	// 	i++;
	// }
	// while(input[i] != 0x20)
	// {
	// 	arg2[i] = input[i];
	// 	i++;
	// }

	char tokens[3][16];
	int8_t last_null = -1;
	int8_t j = 0;
	for(int8_t i = 0; i < MAX_INPUT_LENGTH; i++)
	{
		if((input[i] == 0x20) && (input[i+1] != 0x20))
		{
			input[i] = 0;
			strcpy(tokens[j],&input[last_null + 1]);
			last_null = i;
			j++;
		}
		else if(input[i] == 0x20)
		{
			input[i] = 0;
		}
		i++;
	}
	printf("1: %s, 2: %s, 3: %s\r\n", tokens[0], tokens[1], tokens[2]);


	return output;
}