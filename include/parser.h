#ifndef parser_h
#define parser_h

#include "state_machine.h"

char *read_program(char **argv, int *num_states);
void print_char_array(char *charr);
void append_word_buffer(char *word_buffer, unsigned *count, char ch);
void parse_program(char *program, state_machine *sm);
#endif

