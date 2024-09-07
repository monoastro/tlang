#include "state_machine.h"
#include <stdio.h>
#include <stdlib.h>

head_operation headop_converter(char operation)
{
	switch(operation)
	{
		case 'L':
			return LEFT;
		case 'S':
			return STAY;
		case 'R':
			return RIGHT;
		default:
			printf("Unrecognized head operation symbol. You sure you know what you're doing?\n");
			exit(1);
	}
}


cell_operation cellop_converter(char operation)
{
	switch(operation)
	{
		case 'N':
			return NOCHANGE;
		case 'F':
			return FLIP;
		default:
			printf("Unrecognized cell operation symbol. I don't think you know what you're doing.\n");
			exit(1);
	}
}

int transition_converter(char *word_buffer)
{
	if(word_buffer[0] == 'H') return HLT;
	else return atoi(word_buffer);
}

void state_interpreter(state_machine *sm, tape *tp)
{
	//if hashmapped this would be like, hey hashmap does this state_identifier exist? i.e. .contains() method of cpp
	if(sm->active_state > sm->num_states - 1 || sm->active_state < 0)
	{
		printf("\033[1;31mGiven state not found.\033[1;0m\nTip: States are (currently) identified by the order in which they're written. Rewrite the program to point to proper states.");
		exit(1);
	}
	if(sm->head > tp->num_cells - 1 )
	{
		printf("The head is outside the tape. Wait until I make it dynamically added");
		exit(1);
	}

	if(tp->cell[sm->head] == 1)
	{
		tp->cell[sm->head] ^= sm->states[sm->active_state].cell_operation_if[1];
		sm->head += sm->states[sm->active_state].head_operation_if[1];
		sm->active_state = sm->states[sm->active_state].transition_if[1];
	}
	else if(tp->cell[sm->head] == 0)
	{
		tp->cell[sm->head] ^= sm->states[sm->active_state].cell_operation_if[0];	
		sm->head += sm->states[sm->active_state].head_operation_if[0];
		sm->active_state = sm->states[sm->active_state].transition_if[0];
	}
	else if(tp->cell[sm->head] == 2) 
	{
		
	}
}
