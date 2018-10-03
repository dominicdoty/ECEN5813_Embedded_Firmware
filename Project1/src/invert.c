/*
 * invert.c
 * @brief inverts a memory range
 * @author D.Doty
*/

/* Includes */
#include "invert.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t invert(char* args)
{
	// Parse arguments
	uint64_t address = 0;
	uint64_t word_qty = 1;	// Default. If no word qty supplied, assumed user just wants to invert the supplied address
	io_parse(args, 2, &address, &word_qty);

	// Check if the provided memory address and word quantity are in allocated block
	// Get user confirmation to proceed if they're out of range
	if(valid_range(address, word_qty) != 0)
	{
		// User has indicated they don't want to proceed. Returns to main for a new command
		return 1;
	}

	// Invert
	printf("Inverting...\n");
	clock_t begin = clock();

	// Loop through specified address range inverting each entry
	for(uint64_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		*((uint32_t*)(address + i)) ^= 0xFFFFFFFF;
	}

	clock_t end = clock();
	// Calculate execution time in uS to avoid floating point
	uint64_t execution_time = (1000000*(uint64_t)(end - begin))/CLOCKS_PER_SEC;
	printf("Execution time: %lu uS\n\n",execution_time);
	return 0;
}