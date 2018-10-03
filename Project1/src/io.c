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
// Gets user input and matches the first word to a command in the command table
// everything after the first whitespace or newline is passed on to the command as arguments
// If no command is matched, it returns -1 and writes an error message
struct io cmd_get()
{
	// Init output structure
	struct io output;
	output.command = -1;

	// Declare and take in input
	char input[MAX_INPUT_LENGTH];
	if(!fgets(input, MAX_INPUT_LENGTH, stdin))
	{
		exit(1);
	}
	printf("\n");

	// Split the input into command and args (splits at first space or newline)
	char token[MAX_INPUT_LENGTH];	// Token stores the command string
	token[0] = 0;

	// Loop through input string looking for spaces or newlines
	for(uint8_t i = 0; i < MAX_INPUT_LENGTH; i++)
	{
		// If char is a space or newline
		if((input[i] == 0x20) || (input[i] == 0x0A))
		{
			// Set the space or newline to a null and use copy to move command into token
			input[i] = 0;
			strcpy(&token[0],&input[0]);
			strcpy(output.args,&input[i+1]);
			break;
		}
	}

	// Turn the command token into a command index #
	// Loop through the command table and compare table to input char by char for a match
	for(int8_t command_index = 0; command_index < command_quantity; command_index++)
	{
		// Loop through the input string and compare char by char
		uint8_t char_index = 0;
		while(token[char_index] == command_human[command_index][char_index])
		{
			char_index++;
			// If both the input and the command table show a null, then the whole command matched
			if((token[char_index] == 0) && (command_human[command_index][char_index] == 0))
			{
				output.command = command_index;
				return output;
			}
		}
	}
	printf("Invalid command, try 'help'\n\n");
	return output;
}

// Turn and argument string into numbers in variables
// Variadic function. User provides how many arguments they expect to get
// and addresses where they want to store them.
// Function splits the string on whitespaces or newlines and turns each chunk
// into a number. 0x is converted as hex, otherwise converted as decimal
void io_parse(char* arg_string, uint8_t arg_qty, ...)
{
	// Initialize macros for keeping track of variadic arguments
	va_list arg_ptr;
	va_start(arg_ptr, arg_qty);
	uint8_t arg_end;

	// Loop for each expected argument
	while(arg_qty > 0)
	{
		// Take in the pointer to the output variable
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
		
		// Check for #, indicates special argument
		if(arg_string[0] == 0x23)
		{
			// Need to flesh this out into a whole function for different #'s
			*var_ptr = (uint64_t)block_ptr;
		}
		else
		{
			// Turn the first arg into a number and put it in the variable
			*var_ptr = string_num(arg_string);
		}
		// Move the string pointer down to the next part of the list
		arg_string = &arg_string[arg_end + 1];
		arg_qty--;
	}

	// Input ends with a newline then a null. The last thing left in input
	// should be a null. If it isn't, then we have more arguments than the prog expected
	if(arg_string[0] != 0)
	{
		printf("Too many args or trailing spaces, ignoring extras\n\n");
	}
}

// Determines if a string is hex or decimal and calls appropriate conversion
uint64_t string_num(char* string)
{
	uint64_t result = 0;

	//determine if its hex or decimal and call the appropriate func
	// if string starts with 0X or 0x its hex
	if((string[0] == '0') && ((string[1] == 'x')||(string[1] == 'X')))
	{
		result = string_hex(&string[2]); //string[2] cuts off the '0x'
	}
	else
	{
		result = string_dec(string);
	}
	return result;
}

// Converts decimal string to number
uint64_t string_dec(char* string)
{
	uint8_t length = strlen(string);
	uint64_t result = 0;

	// Loop through input string, multiplying each number by its 10 power
	for(int8_t i = length - 1; i >= 0; i--)
	{
		// Check if char is outside ASCII range for numbers
		if(string[i] < 0x30 || string[i] > 0x39)
		{
			printf("Argument '%s' was not valid decimal. If you wanted hex, prepend with '0x'\n\n",string);
			return 0;
		}
		result += ((uint8_t)(string[i] - 0x30))*power(10,length -1 - i);
	}
	return result;
}

// Converts hex string to number
uint64_t string_hex(char* string)
{
	uint8_t length = strlen(string);
	uint64_t result = 0;
	uint8_t value = 0;

	// Loop through input string, multiplying each number by its 16 power
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

// General integer exponentiation
uint64_t power(uint32_t base, uint32_t exponent)
{
	uint64_t result = 1;
	for(uint8_t i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

// Verify a given address and range are inside allocated memory
// If they are not, prompt the user if they want to proceed
int8_t valid_range(uint64_t address, uint64_t word_qty)
{
	char response[4] = "";	// Response string

	// Check if memory is allocated
	if(block_ptr == NULL)
	{
		printf("No memory allocated, Proceed? (y/n)\n");
		fgets(response, 3, stdin);
	}	// Check if given address and word qty fit in allocated memory
	else if((address < (uint64_t)block_ptr) || ((address + (word_qty - 1)*sizeof(uint32_t)) > ((uint64_t)block_ptr + (block_size - 1)*sizeof(uint32_t))))
	{
		printf("Attempting to access memory out of the allocated range, Proceed? (y/n)\n");
		fgets(response, 3, stdin);
	}

	// Act according to response
	if(response[0] == 0)
	{
		return 0;	// Address and range are acceptable
	}
	else if((response[0] == 'y') || (response[0] == 'Y'))
	{
		return 0;	// Address and range are not acceptable, but user overrides
	}
	else
	{
		return 1;	// Address and range are not acceptable, user acquiesces 
	}
}