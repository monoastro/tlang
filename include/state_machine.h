#ifndef state_machine_h
#define state_machine_h

#include "tape.h"

#define HLT -1

typedef enum 
{
	LEFT = -1,
	STAY = 0,
	RIGHT = 1,
} head_operation;
typedef enum 
{
	NOCHANGE = 0,
	FLIP = 1,
} cell_operation;

/*
//format
identifier cell_operationIf0 head_operationIf0 transitionIf0 cell_operationIf1 head_operationIf1 transitionIf1

//example program in my head that changes 00 -> 10 -> 11 -> 01
1 RIGHT 1 0 RIGHT 1
1 LEFT 0 0 LEFT 0
*/

typedef struct
{
	//usless because the index of the array acts as the identifier
	//int identifier;
	cell_operation cell_operation_if[3];
	head_operation head_operation_if[3];
	int transition_if[3];
} state;

typedef struct
{
	state *states; //todo: identifier could be used if you make this a hashmap
	int active_state; //had to make it an int for the halting state identifier
	size_t head;
	int num_states;
} state_machine;

head_operation headop_converter(char operation);
cell_operation cellop_converter(char operation);
int transition_converter(char *word_buffer);
void state_interpreter(state_machine *sm, tape *tp);
#endif
