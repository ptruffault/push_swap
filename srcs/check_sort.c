#include "checker.h"

int	check_sort(t_instruct *ins)
{
	int i;

	i = -1;
	if (ins->b->size > 0)
		return (0);
	while (++i < (int)ins->a->size - 1)
		if (ins->a->t[i] > ins->a->t[i + 1]
			|| ins->pa->t[i] != i)
			return (0);
	return (1);
}