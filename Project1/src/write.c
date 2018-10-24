/*
 * write.c
 * @brief function to write a memory location
 * @author D.Doty
*/

/* Includes */
#include "write.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t write(char* args)
{
	// Parse arguments
	uint64_t address = 0;
	uint64_t word = 0;
	io_parse(args, 2, &address, &word);

	// Check if the provided memory address and word quantity are in allocated block
	// Get user confirmation to proceed if they're out of range
	if(valid_range(address, 1) != 0)
	{
		// User has indicated they don't want to proceed. Returns to main for a new command
		return 1;
	}

	// Write
	printf("Writing...\n");
	printf("Address\t\t\tContents Hex\tContents Dec\n");
	*((uint32_t*)address) = word;
	printf("0x%016I64X\t0x%08I32X\t%I32u\n\n", address, *((uint32_t*)address), *((uint32_t*)address));
	return 0;
}