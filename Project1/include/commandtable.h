/*
 * command table.h
 * @brief arrays to hold commands and functions to create and interact with them
 * @author D.Doty
*/

/* Header Guard */
#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H

/* Includes */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

/* Defines */
typedef int8_t (*command_proto)(uint32_t, uint32_t);

/* Global Variables */
extern char** command_human;
extern char** command_help;
extern command_proto* command_table;
extern uint8_t command_quantity;

/* Global Function Prototypes */

// Creates the empty command table
int8_t command_table_init(uint8_t num_of_commands);

// Adds a command to the command table
int8_t add_command(char* human_name, char* help_msg, command_proto func_pointer);

#endif //COMMANDTABLE_H
