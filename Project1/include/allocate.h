/*
 * allocate.h
 * @brief command to allocate memory
 * @author D.Doty
*/

/* Header Guard */
#ifndef ALLOCATE_H
#define ALLOCATE_H

/* Includes */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "io.h"

/* Defines */


/* Global Variables */
extern uint32_t* block_ptr;
extern uint32_t block_size;

/* Global Function Prototypes */
int8_t allocate(char* args);

#endif //ALLOCATE_H
