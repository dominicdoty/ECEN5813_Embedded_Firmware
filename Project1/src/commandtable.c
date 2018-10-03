/*
 * commandtable.c
 * @brief arrays to hold commands and functions to create and interact with them
 * @author D.Doty
*/

// Note: not sure if I'm allowed to use string functions or if I have to write my own.
// Using lib for now, will change if necessary

/* Includes */

#include "commandtable.h"

/* Defines */


/* Global Variables */
char** command_human = NULL;
char** command_help = NULL;
command_proto* command_table = NULL;
uint8_t command_quantity = 0;

/* Private Function Prototypes */


/* Function Definition */
// Creates tables to hold the user command names, help messages, and function pointers
int8_t command_table_init(uint8_t num_of_commands)
{
	// Don't allow initialization if it's already been done
	if(command_quantity) 
	{
		printf("ERROR:Command Table Double Inititialization\n");
		return 1;
	}

	// Store size of table
	command_quantity = num_of_commands;

	// Allocate the array of strings for human readable commands
	command_human = (char**)malloc(command_quantity * sizeof(char*));
	if(!command_human)
	{
		printf("ERROR:Command Table Initialization, Human Readable Array\n");
		return 1;
	}

	// Allocate the array of strings for command help messages
	command_help = (char**)malloc(command_quantity * sizeof(char*));
	if(!command_help)
	{
		printf("ERROR:Command Table Initialization, Help Messages\n");
		return 1;
	}

	// Allocate the array of function pointers
	command_table = (command_proto*)malloc(command_quantity * sizeof(command_proto*));
	if(!command_table)
	{
		printf("ERROR:Command Table Initialization, Function Pointer Array\n");
		return 1;
	}

	return 0;
}

// Adds a command to the table created with command_table_init
int8_t add_command(char* human_name, char* help_msg, command_proto func_pointer)
{
	static uint8_t command_table_index = 0;

	// Catch too many functions added to table
	if(command_table_index > (command_quantity-1)) 
	{
		printf("ERROR:More Commands Initialized Than Table Size\n");
		return 1;
	}

	// Allocate and fill the Human Readable Command Name
	command_human[command_table_index] = (char*)malloc(strlen(human_name + 1));	//plus one for null
	strcpy(command_human[command_table_index], human_name);				//copy the fed name into the array

	// Allocate and fill the Help Message array
	command_help[command_table_index] = (char*)malloc(strlen(help_msg + 1));	//plus one for null
	strcpy(command_help[command_table_index], help_msg);				//copy the help message in

	// Fill the function pointer in
	command_table[command_table_index] = func_pointer;					//copy the func pointer into the table

	// Index
	command_table_index++;	//increment the table so it will fill the next slot next time

	return 0;
}
