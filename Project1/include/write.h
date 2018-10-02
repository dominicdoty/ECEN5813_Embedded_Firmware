/*
 * write.h
 * @brief function to write a memory location
 * @author D.Doty
*/

/* Header Guard */
#ifndef WRITE_H
#define WRITE_H

/* Includes */
#include <stdio.h>
#include <stdint.h>
#include "io.h"

/* Defines */


/* Global Variables */
extern uint32_t* block_ptr;
extern uint32_t block_size;

/* Global Function Prototypes */
int8_t write(char* args);

#endif //WRITE_H
