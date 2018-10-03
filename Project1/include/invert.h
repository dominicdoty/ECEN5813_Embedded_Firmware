/*
 * invert.h
 * @brief inverts a memory range
 * @author D.Doty
*/

/* Header Guard */
#ifndef INVERT_H
#define INVERT_H

/* Includes */
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "io.h"

/* Defines */


/* Global Variables */
extern uint32_t* block_ptr;
extern uint32_t block_size;

/* Global Function Prototypes */
int8_t invert(char* args);

#endif //INVERT_H
