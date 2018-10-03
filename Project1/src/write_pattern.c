/*
 * write_pattern.c
 * @brief writes a pseudorandom pattern to a memory range
 * @author D.Doty
*/

/* Includes */
#include "write_pattern.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t write_pattern(char* args)
{
	// Parse arguments
	uint64_t address = 0;
	uint64_t word_qty = 1;	// Default. If user does not put value, it assumes they only want to write the provided address
	uint64_t seed = 1;		// Default. If user does not supply seed, it is assumed to be zero.
	io_parse(args, 3, &address, &word_qty, &seed);

	// Check if the provided memory address and word quantity are in allocated block
	// Get user confirmation to proceed if they're out of range
	if(valid_range(address, word_qty) != 0)
	{
		// User has indicated they don't want to proceed. Returns to main for a new command
		return 1;
	}

	// Write PRNG Pattern to Memory
	printf("Writing PRN's...\n");
	clock_t begin = clock();
	uint32_t last = xorshift((uint32_t)seed);
	for(uint64_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		// Looping through provided addresses and writing PRN's
		*((uint32_t*)(address + i)) = last;
		// Generate a new PRN for next loop
		last = xorshift(last);
	}
	clock_t end = clock();
	// Calculating execution time in uS to avoid floating point math
	uint64_t execution_time = (1000000*(uint64_t)(end - begin))/CLOCKS_PER_SEC;
	printf("Execution time: %lu uS\n\n",execution_time);
	return 0;
}