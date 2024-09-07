#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tape.h"
#include "state_machine.h"
#include "parser.h"

int main(int argc, char **argv)
{
	if(argc<2)
	{
		printf("%s: \033[1;31mfatal error:\033[1;0m no input files\ninterpretation terminated.\n", argv[0]);
		printf("usage: %s filename.turing\n", argv[0]);
		exit(1);
	}
    int filename_len = strlen(argv[1]);
    if (filename_len < 8 || strcmp(argv[1] + filename_len - 7, ".turing") != 0)
	{
        printf("%s: \033[1;31mfile format not recognized\033[1;0m\n", argv[0]);
        printf("usage: %s filename.turing\n", argv[0]);
        exit(1);
    }

	tape tp;
	tp.num_cells = 100;
	tp.cell = (int*)malloc(tp.num_cells*sizeof(int));
	memset(tp.cell, 0, tp.num_cells*sizeof(int));

	state_machine alan = {0};
	char *program = read_program(argv, &alan.num_states);
	alan.states = (state*)malloc(sizeof(state)*alan.num_states);
	parse_program(program, &alan);
	free(program);

	tape_print(&tp, &alan.head);
	do
	{
		sleep(1);
		state_interpreter(&alan, &tp);
		tape_print(&tp, &alan.head);
	} while(alan.active_state != HLT);
	printf("\033[1;32mProgram has halted sucesssfully.\033[1;0m");

	//do i even need to free these at this point?
	//dumbasses with their ohh you should always free the memory after allocating it, stfu book nerds y'ain't know shit about memory
	//free(tp.cell);
	//free(alan.states);
	return 0;
}
