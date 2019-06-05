#include "checker.h"

int is_already_sorted(t_instruct *ins)
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	while (++i < ins->a->size)
	{
		if (ins->pa->t[i] == 0)
			ret = i;
		if (ins->pa->t[i] + 1 != ins->pa->t[i + 1]
			&& ins->pa->t[i + 1] != 0)
			return (0);
	}
	return (ret);
}

char *where_to_go(t_instruct *ins)
{
	int i;

	i = 0;
	while (i < ins->size && ins->a->t[i] < ins->a->t[i + 1])
		i++;
	if (i > ins->size / 2)
		return ("rra");
	else
		return ("ra");


}

void only_swap(t_instruct *ins)
{
	int zero;

	while (!check_sort(ins))
	{
		if (ins->a->size > 4 && ins->pa->t[0] == ins->pa->size - 1)
			move(ins, "pb", TRUE);
		else if (ins->pa->t[0] > ins->pa->t[1] && !(ins->pa->t[0] == ins->pa->size - 1 && ins->pa->t[1] == 0))
			move(ins, "sa", TRUE);
		else if ((zero = is_already_sorted(ins)) > 0)
		{
			if (zero > ins->a->size / 2)
				nmove(ins, "rra", ins->a->size - zero);
			else
				nmove(ins, "ra", zero);
			while (ins->b->size > 0)
			{
				move(ins, "pa", TRUE);
				move(ins, "ra", TRUE);
			}
		}
		else
			move(ins, where_to_go(ins), TRUE);
		//putpile(ins);
	}
}

int	easy_sort(t_instruct *ins)
{
	int zero;

	if ((zero = is_already_sorted(ins)) > 0)
	{
		if (zero > ins->a->size / 2)
			nmove(ins, "rra", ins->a->size - zero);
		else
			nmove(ins, "ra", zero);
	}
	else
		only_swap(ins);
	return (1);
}

int main(int argc, char **argv)
{
	t_instruct i;

	if (init_instruction(&i, argv, argc))
	{
		easy_sort(&i);
		free_instruct(&i);
	}
	return (0);
}