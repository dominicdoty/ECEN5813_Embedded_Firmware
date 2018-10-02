/*
 * dealloc.h
 * @brief frees allocated memory
 * @author D.Doty
*/

/* Header Guard */
#ifndef DEALLOC_H
#define DEALLOC_H

/* Includes */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Defines */


/* Global Variables */
extern uint32_t* block_ptr;
extern uint32_t block_size;

/* Global Function Prototypes */
int8_t dealloc(char* ignore);

#endif //FREE_H
