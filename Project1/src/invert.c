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
	uint64_t word_qty = 1;
	io_parse(args, 2, &address, &word_qty);

	// Check for valid inputs
	if(valid_range(address, word_qty) != 0)
	{
		return 1;
	}

	// Invert
	printf("Inverting...\n");
	clock_t begin = clock();
	for(uint64_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		*((uint32_t*)address) ^= 0xFFFFFFFF;
	}
	clock_t end = clock();
	uint64_t execution_time = (1000000*(uint64_t)(end - begin))/CLOCKS_PER_SEC;
	printf("Execution time: %lu uS\n\n",execution_time);
	return 0;
}