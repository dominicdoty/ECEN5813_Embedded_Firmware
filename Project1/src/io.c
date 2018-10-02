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
	char* temp_args = arg_string;
	uint8_t arg_end = 0;

	while(arg_qty > 0)
	{
		// Take in the pointer to the variable
		uint64_t* var_ptr = va_arg(arg_ptr, uint64_t*);

		// Loop through the arg_string to get the first arg
		arg_end = 0;
		while(!((temp_args[arg_end] == 0x20) || (temp_args[arg_end] == 0x0A)))
		{
			arg_end++;
			if(arg_end > MAX_INPUT_LENGTH)
			{
				printf("Supplied arguments are not correct, refer to help\n\n");
				return;
			}
		}
		// Drop a null in
		temp_args[arg_end] = 0;
		// Turn the first arg into a number and put it in the variable
		*var_ptr = string_num(temp_args);
		// Move the string pointer down to the next part of the list
		temp_args = &temp_args[arg_end + 1];
		arg_qty--;
	}

	if(temp_args[0] != 0)
	{
		printf("More arguments supplied than required, ignoring extras\n\n");
	}
}

uint32_t string_num(char* string)
{
	uint32_t result = 0;

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

uint32_t string_dec(char* string)
{
	uint8_t length = strlen(string);
	uint32_t result = 0;
	for(int8_t i = length - 1; i >= 0; i--)
	{
		if(string[i] < 0x30 || string[i] > 0x39)
		{
			printf("Argument '%s' was not valid decimal\n\n",string);
			return 0;
		}
		result += ((uint8_t)(string[i] - 0x30))*power(10,length -1 - i);
	}
	return result;
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
				return 0;
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