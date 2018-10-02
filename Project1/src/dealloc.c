/*
 * dealloc.c
 * @brief frees allocated memory
 * @author D.Doty
*/

/* Includes */
#include "dealloc.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t dealloc(char* ignore)
{
	if(block_ptr != NULL)
	{
		free(block_ptr);
		block_ptr = NULL;
		block_size = 0;
		printf("Block freed\n\n");
		return 1;
	}
	else
	{
		printf("No memory allocated\n\n");
		return -1;
	}

}