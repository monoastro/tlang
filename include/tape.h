#ifndef tape_h
#define tape_h

#include <stdbool.h>
#include <unistd.h>

typedef struct
{
	int *cell;
	size_t num_cells;
} tape;
void tape_print(const tape* tp, const size_t *head);
#endif
