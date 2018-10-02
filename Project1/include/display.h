/*
 * display.h
 * @brief function to display a memory location
 * @author D.Doty
*/

/* Header Guard */
#ifndef DISPLAY_H
#define DISPLAY_H

/* Includes */
#include <stdio.h>
#include <stdint.h>
#include "io.h"

/* Defines */


/* Global Variables */
extern uint32_t* block_ptr;
extern uint32_t block_size;

/* Global Function Prototypes */
int8_t display(char* args);

#endif //DISPLAY_H
