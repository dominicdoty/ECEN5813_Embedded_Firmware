/*
 * allocate.c
 * @brief command to allocate memory
 * @author D.Doty
*/

/* Includes */
#include "allocate.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t allocate(char* args)
{
	uint64_t qty_words = 0;
	io_parse(args, 1, &qty_words);

	if(qty_words == 0)
	{
		printf("Cannot allocate 0 words\n\n");
		return 1;
	}

	if(block_ptr != NULL)
	{
		printf("Memory has already been allocated. Please free before allocating again\n\n");
		return 1;
	}

	block_ptr = (uint32_t*)malloc(sizeof(uint32_t) * qty_words);
	
	if(block_ptr == NULL)
	{
		printf("Not enough memory to allocate requested amount.\n\n");
		return 1;
	}

	block_size = qty_words;
	printf("Allocated a block starting at address 0x%016lX, %d uint32's long\n\n",(uint64_t)block_ptr, block_size);
	return 0;
}
