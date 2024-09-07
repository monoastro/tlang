#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define WORDS_IN_STATE  7 
#define WORD_BUFFER_MAX_SIZE 10

char *read_program(char **argv, int *num_states)
{
	FILE *file = fopen(argv[1], "r");
	if(!file) 
	{
		printf("%s: \033[1;31mfatal error:\033[1;0m %s: No such file or directory\ninterpretion terminated.\n", argv[0], argv[1]);
		exit(1);
	}
		
	fseek(file, 0L, SEEK_END);
	unsigned num_char = ftell(file);
	//printf("%u %d\n", num_char, *num_states); //\n is included here
	rewind(file);
	char *program = (char*)malloc(sizeof(char)*num_char);
	fread(program, sizeof(char), num_char, file);
	fclose(file);
	
	//check if someone tries to compile an empty or an incomplete file
	assert(num_char>0);
	unsigned space_counter = 0, index = 0;
	while(program[index] != '\0')
	{
		char ch = program[index++];
		if(ch == '\n') 
		{
			*num_states = *num_states + 1;
			assert(space_counter == WORDS_IN_STATE - 1);
			space_counter = 0;
		}
		else if(ch == ' ')
		{
			space_counter++;
		}
	}
	return program;
}
//bruh moment printf("%s", program);
void print_char_array(char *charr)
{
	size_t index = 0;
	do
	{
		printf("%c", charr[index++]);
	} while(charr[index] != '\0');
}

void append_word_buffer(char *word_buffer, unsigned *count, char ch) 
{
    if (*count < WORD_BUFFER_MAX_SIZE)
	{
        word_buffer[*count] = ch;
        (*count)++;
    } else {
        printf("no buffer overflow here buddy\nuse a sensible state identifier");
		exit(1);
    }
}
void parse_program(char *program, state_machine *sm)
{
	unsigned index = 0, state_offset = 0, word_offset = 0;
	//the biggest word length that this buffer needs to support is the size of the state identifier
	//well, state array index to be completely real, so size should be the max size of num_states
	//which is size_t; unsigned long integer; which is 18446744073709551615; which is 20 digits
	
	//ignore the stuff above, i had to change the type of num_states from size_t to int because
	//active_state had to be changed to int to make room for HLT as -1
	//as such the word buffer's max size has to be reduced now from 20 to
	//num_digits(2^(sizeof(int)*8)) = num_digits(2147483648 unique states) = 10
	char word_buffer[WORD_BUFFER_MAX_SIZE] = {0};
	unsigned word_buffer_count = 0;

	//the worst case I'm willing to accept here as a valid program is
	//000 O R 111 Z R 111
	//111 O L 000 Z L 000
	while( program[index] != '\0')
	{
		/*
		//comments got hands
		if(program[index] == '/' && program[index+1] == '/')
		{
			while(program[index++]!='\n');
			state_offset++;
			continue;
		}
		*/
		append_word_buffer(word_buffer, &word_buffer_count, program[index++]);
		//printf("%s\n---\n", word_buffer);

		char next = program[index];

		if (next == ' ' || next == '\n') 
		{
			//printf("Word %u detected: %s\n", word_offset, word_buffer);
			switch(word_offset)
			{
				case 0:
					//printf("moshi moshi useless identifier desu. %s\n", word_buffer);
					//sm->states[state_offset].identifier = atol(word_buffer); //waiting for the hashmap
					break;
				case 1:
					sm->states[state_offset].cell_operation_if[0] = cellop_converter(word_buffer[0]);
					break;
				case 2:
					sm->states[state_offset].head_operation_if[0] = headop_converter(word_buffer[0]);
					break;
				case 3:
					sm->states[state_offset].transition_if[0]	 = transition_converter(word_buffer);
					//printf("Third word here, parsed identifier: %d\n", sm->states[state_offset].transition_if[0]);
					break;
				case 4:
					sm->states[state_offset].cell_operation_if[1] = cellop_converter(word_buffer[0]);
					break;
				case 5:
					sm->states[state_offset].head_operation_if[1] = headop_converter(word_buffer[0]);
					break;
				case 6:
					sm->states[state_offset].transition_if[1]	 = transition_converter(word_buffer);
					//printf("Sixth word here, parsed identifier: %d\n", sm->states[state_offset].transition_if[1]);
					break;
				default:
					printf("Your code sucks ass\n");
					exit(1);
			}

			if(next == '\n')
			{
				state_offset++;
				word_offset = 0;
			}
			else
			{
				word_offset++;
			}

			index++;
			memset(word_buffer, 0, sizeof(word_buffer));
			word_buffer_count = 0;
		}
	} 
	printf("\033[1;34mProgram parsed successfully.\033[1;0m\n");
}

/*
//hardcode the program for now, well, programs are kinda the definition of hardcoded anyway
//alan.states[0].identifier = 0;
alan.states[0].cell_operation_if[0] = 1;
alan.states[0].head_operation_if[0] = RIGHT;
alan.states[0].transition_if[0] = 1;
alan.states[0].cell_operation_if[1] = 0;
alan.states[0].head_operation_if[1] = RIGHT;
alan.states[0].transition_if[1] = 1;

//alan.states[1].identifier = 1;
alan.states[1].cell_operation_if[0] = 1;
alan.states[1].head_operation_if[0] = LEFT;
alan.states[1].transition_if[0] = 0;
alan.states[1].cell_operation_if[1] = 0;
alan.states[1].head_operation_if[1] = LEFT;
alan.states[1].transition_if[1] = 0;
*/
