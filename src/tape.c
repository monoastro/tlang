#include "tape.h"
#include <stdio.h>

void tape_print(const tape* tp, const size_t *head)
{
	for(size_t i = 0; i<tp->num_cells; i++)
	{
		if(i == *head) printf("\033[1;32m");
		else printf("\033[1;35m");
		printf("%d\033[1;0m", tp->cell[i]);
	}
	printf("\n\n");
}
