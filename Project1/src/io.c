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


/* Function Definition */
struct io io_get()
{
	// Define io_get so we can dump out nulls at any error later
	struct io output = {0, 0, 0};

	// Declare and take in input
	char input[MAX_INPUT_LENGTH];
	fgets(input, MAX_INPUT_LENGTH, stdin);
	printf("\n");

	// Check for problems
	uint8_t length = strlen(input);
	if(length >= MAX_INPUT_LENGTH - 1)
	{
		printf("Error, your command was too long to be valid. Type 'help' for help\n\n");
		return output;
	}

	// Split the input into tokens
	char tokens[3][16];
	tokens[0][0] = 0;
	tokens[1][0] = 0;
	tokens[2][0] = 0;
	int8_t last_null = -1;
	int8_t j = 0;
	for(int8_t i = 0; i < MAX_INPUT_LENGTH; i++)
	{
		if(j > 2){break;} 

		if(input[i] == 0xA)
		{
			input[i] = 0;
			strcpy(tokens[j],&input[last_null + 1]);
			break;
		}

		if(input[i] == 0x20)
		{
			if(input[i-1] != 0)
			{
				input[i] = 0;
				strcpy(tokens[j],&input[last_null + 1]);
				last_null = i;
				j++;
			}
			else
			{
				input[i] = 0;
				last_null = i;
			}
		}
	}

	// Turn the tokens into useful info
	output.arg1 = string_hex(tokens[1]);
	output.arg2 = string_hex(tokens[2]);

	// Turn the command token into a command index #
	output.command = -1;
	for(int8_t command_index = 0; command_index < command_quantity; command_index++)
	{
		uint8_t char_index = 0;
		while(tokens[0][char_index] == command_human[command_index][char_index])
		{
			char_index++;
			if((tokens[0][char_index] == 0) && (command_human[command_index][char_index] == 0))
			{
				output.command = command_index;
			}
		}
	}
	if(output.command == -1)
	{
		printf("Invalid command, try 'help'\n\n");
	}

	return output;
}

uint32_t string_hex(char* string)
{
	uint8_t length = strlen(string);
	uint32_t result = 0;

	for(int8_t i = length - 1; i >= 0; i--)
	{
		switch (string[i])
		{
			case 0:
				result = 0;
				break;
			case 0x30:
				break;
			case 0x31:
				result += 1*power(16,length -1 - i);
				break;
			case 0x32:
				result += 2*power(16,length -1 - i);
				break;
			case 0x33:
				result += 3*power(16,length -1 - i);
				break;
			case 0x34:
				result += 4*power(16,length -1 - i);
				break;
			case 0x35:
				result += 5*power(16,length -1 - i);
				break;
			case 0x36:
				result += 6*power(16,length -1 - i);
				break;
			case 0x37:
				result += 7*power(16,length -1 - i);
				break;
			case 0x38:
				result += 8*power(16,length -1 - i);
				break;
			case 0x39:
				result += 9*power(16,length -1 - i);
				break;
			case 0x41:
				result += 10*power(16,length -1 - i);
				break;
			case 0x42:
				result += 11*power(16,length -1 - i);
				break;
			case 0x43:
				result += 12*power(16,length -1 - i);
				break;
			case 0x44:
				result += 13*power(16,length -1 - i);
				break;
			case 0x45:
				result += 14*power(16,length -1 - i);
				break;
			case 0x46:
				result += 15*power(16,length -1 - i);
				break;
			default:
				printf("Argument '%s' was not valid hex\n\n",string);
				result = 0;
				return result;
		}
	}
	return result;
}

// General integer exponentiation. probably moving to separate lib
uint32_t power(uint32_t base, uint32_t exponent)
{
	uint32_t result = 1;
	for(uint8_t i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}