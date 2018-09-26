/*
 * help.h
 * @brief display help dialog to get user started
 * @author D.Doty
*/

/* Header Guard */
#ifndef HELP_H
#define HELP_H

/* Includes */

#include <stdio.h>
#include <stdint.h>
#include "commandtable.h"

/* Defines */


/* Global Variables */


/* Function Prototypes */

void help_welcome();

int8_t help(uint32_t disregard, uint32_t disregard2);

#endif //HELP_H
