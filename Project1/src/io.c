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
struct io cmd_get()
{
	struct io output;

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

	// Split the input into command and args (splits at first space)
	char token[MAX_INPUT_LENGTH];
	token[0] = 0;

	for(uint8_t i = 0; i < MAX_INPUT_LENGTH; i++)
	{
		if((input[i] == 0x20) || (input[i] == 0x0A))
		{
			input[i] = 0;
			strcpy(&token[0],&input[0]);
			strcpy(output.args,&input[i+1]);
			break;
		}
	}

	// Turn the command token into a command index #
	output.command = -1;
	for(int8_t command_index = 0; command_index < command_quantity; command_index++)
	{
		uint8_t char_index = 0;
		while(token[char_index] == command_human[command_index][char_index])
		{
			char_index++;
			if((token[char_index] == 0) && (command_human[command_index][char_index] == 0))
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

void io_parse(char* arg_string, uint8_t arg_qty, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, arg_qty);
	uint8_t arg_end = 0;

	while(arg_qty > 0)
	{
		// Take in the pointer to the variable
		uint64_t* var_ptr = va_arg(arg_ptr, uint64_t*);

		// Loop through the arg_string to get the first arg
		arg_end = 0;
		while(!((arg_string[arg_end] == 0x20) || (arg_string[arg_end] == 0x0A)))
		{
			arg_end++;
			if(arg_end > MAX_INPUT_LENGTH)
			{
				return;
			}
		}
		// Drop a null in
		arg_string[arg_end] = 0;
		// Turn the first arg into a number and put it in the variable
		*var_ptr = string_num(arg_string);
		// Move the string pointer down to the next part of the list
		arg_string = &arg_string[arg_end + 1];
		arg_qty--;
	}

	if(arg_string[0] != 0)
	{
		printf("Too many args or trailing spaces, ignoring extras\n\n");
	}
}

uint64_t string_num(char* string)
{
	uint64_t result = 0;

	//determine if its hex or decimal and call the appropriate func
	if((string[0] == '0') && ((string[1] == 'x')||(string[1] == 'X')))
	{
		result = string_hex(&string[2]);
	}
	else
	{
		result = string_dec(string);
	}
	return result;
}

uint64_t string_dec(char* string)
{
	uint8_t length = strlen(string);
	uint64_t result = 0;
	for(int8_t i = length - 1; i >= 0; i--)
	{
		if(string[i] < 0x30 || string[i] > 0x39)
		{
			printf("Argument '%s' was not valid decimal. If you wanted hex, prepend with '0x'\n\n",string);
			return 0;
		}
		result += ((uint8_t)(string[i] - 0x30))*power(10,length -1 - i);
	}
	return result;
}

uint64_t string_hex(char* string)
{
	uint8_t length = strlen(string);
	uint64_t result = 0;
	uint8_t value = 0;

	for(int8_t i = length - 1; i >= 0; i--)
	{
		// Number between 0 and 9, convert to number
		if((string[i] >= 0x30) && (string[i] <= 0x39))
		{
			value = (uint8_t)string[i] - 0x30;
		}
		// Number between A and F, convert to 10-15
		else if((string[i] >= 0x41) && (string[i] <= 0x46))
		{
			value = ((uint8_t)string[i]) - 0x37;
		}
		// Number between a and f, convert to 10-15
		else if((string[i] >= 0x61) && (string[i] <= 0x66))
		{
			value = ((uint8_t)string[i]) - 0x57;
		}
		// Invalid character for hex
		else
		{
			printf("Argument '%s' was not valid hex. Remember hex must be prepended with '0x'\n\n",string);
			return 0;
		}
		result += value*power(16,length -1 - i);
	}
	return result;
}

// General integer exponentiation. probably moving to separate lib
uint64_t power(uint32_t base, uint32_t exponent)
{
	uint64_t result = 1;
	for(uint8_t i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

int8_t valid_range(uint64_t address, uint64_t word_qty)
{
	char response[4] = "";

	if(block_ptr == NULL)
	{
		printf("No memory allocated, Proceed? (y/n)\n");
		fgets(response, 3, stdin);
	}
	else if((address < (uint64_t)block_ptr) || ((address + (word_qty - 1)*sizeof(uint32_t)) > ((uint64_t)block_ptr + (block_size - 1)*sizeof(uint32_t))))
	{
		printf("Attempting to access memory out of the allocated range, Proceed? (y/n)\n");
		fgets(response, 3, stdin);
	}

	// Act according to response
	if(response[0] == 0)
	{
		return 0;
	}
	else if((response[0] == 'y') || (response[0] == 'Y'))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}