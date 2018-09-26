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

	// Split the input into tokens
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

		if(j > 2)
		{
			break;
		}
	}
	printf("1: %s, 2: %s, 3: %s\r\n", tokens[0], tokens[1], tokens[2]);

	// Turn the tokens into useful info
	output.arg1 = string_hex(token[1]);
	output.arg2 = string_hex(token[2]);

	printf("arg1: %d, arg2: %d\n", output.arg1, output.arg2);

	return output;
}

uint32_t string_hex(char* string)
{
	uint8_t length = strlen(string);
	uint32_t result = 0;

	for(uint8_t i = length - 1; i >= 0; i--)
	{
		switch (string[i])
		{
			case '0':
				break;
			case '1':
				result += 1*power(16,length -1 - i);
				break;
			case '2':
				result += 2*power(16,length -1 - i);
				break;
			case '3':
				result += 3*power(16,length -1 - i);
				break;
			case '4':
				result += 4*power(16,length -1 - i);
				break;
			case '5':
				result += 5*power(16,length -1 - i);
				break;
			case '6':
				result += 6*power(16,length -1 - i);
				break;
			case '7':
				result += 7*power(16,length -1 - i);
				break;
			case '8':
				result += 8*power(16,length -1 - i);
				break;
			case '9':
				result += 9*power(16,length -1 - i);
				break;
			case 'A':
				result += 10*power(16,length -1 - i);
				break;
			case 'B':
				result += 11*power(16,length -1 - i);
				break;
			case 'C':
				result += 12*power(16,length -1 - i);
				break;
			case 'D':
				result += 13*power(16,length -1 - i);
				break;
			case 'E':
				result += 14*power(16,length -1 - i);
				break;
			case 'F':
				result += 15*power(16,length -1 - i);
				break;
		}
	}
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