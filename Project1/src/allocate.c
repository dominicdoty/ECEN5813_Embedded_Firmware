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
int8_t allocate(uint32_t qty_words, uint32_t ignore)
{
	if(block_ptr != NULL)
	{
		printf("Memory has already been allocated. Please free before allocating again\n\n");
		return -1;
	}

	block_ptr = (uint32_t*)malloc(sizeof(uint32_t) * qty_words);
	
	if(block_ptr == NULL)
	{
		printf("Not enough memory to allocate requested amount.\n\n");
		return -1;
	}

	block_size = qty_words;
	printf("Allocated a block starting at address %X, %d uint32's long\n\n",block_ptr, block_size);
	return 1;
}
