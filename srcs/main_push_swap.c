#include "checker.h"

int zero_position(t_pile *p)
{
	int i;

	i = -1;
	while (++i < p->size)
		if (p->t[i] == 0)
			return (i);
	return (-1);
}

int is_already_sorted(t_instruct *ins)
{
	int i;

	i = -1;
	while (++i < ins->a->size - 1)
		if (ins->pa->t[i] + 1 != ins->pa->t[i + 1]
			&& ins->pa->t[i + 1] != 0)
			return (0);
	return (1);
}

char *where_to_go(t_instruct *ins)
{
	int i;

	i = 0;
	while (i < ins->size && (ins->a->t[i] < ins->a->t[i + 1] || (ins->pa->t[i] == pile_max(ins->pa) && ins->pa->t[i + 1] == 0)))
		i++;
	if (i >= ins->a->size / 2)
		return ("rra");
	else
		return ("ra");
}



void only_swap(t_instruct *ins)
{
	int zero;

	while (!check_sort(ins))
	{
		if (is_already_sorted(ins))
		{
			zero = zero_position(ins->pa);
			if (zero > ins->a->size / 2)
				nmove(ins, "rra", ins->a->size - zero);
			else
				nmove(ins, "ra", zero);
			while (ins->b->size > 0)
				move(ins, "pa", TRUE);
		}
		else if (ins->a->size > 3 && ins->pa->t[0] == pile_min(ins->pa))
			move(ins, "pb", TRUE);
		else if (ins->pa->t[0] > ins->pa->t[1] && !(ins->pa->t[0] == ins->pa->size && ins->pa->t[1] == 0))
			move(ins, "sa", TRUE);
		else
			move(ins, where_to_go(ins), TRUE);
	}
}

int main(int argc, char **argv)
{
	t_instruct i;

	if (init_instruction(&i, argv, argc))
	{
		only_swap(&i);
		free_instruct(&i);
	}
	return (0);
}