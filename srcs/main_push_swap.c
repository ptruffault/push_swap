#include "push_swap.h"

int abs_min(int a, int b)
{
	return (abs(a) < abs(b) ? a : b);
}

void go_to(t_instruct *ins, char pile, int i)
{
	int move;

	//ft_printf("GOTO %i IN %c\n", i, pile);
	//VERIF SI I EST CORRECTDANS LA PILE !!
	if (pile == 'a')
	{
		move = way_selection(ins->pa, i);
		nmove(ins, move > 0 ? "ra" : "rra", abs(move));
	}
	else 
	{
		move = way_selection(ins->pb, i);
		nmove(ins, move > 0 ? "rb" : "rrb", abs(move));
	}
}

int pushing_well(t_pile *p, int pos)
{
	if (pos == 1 || pos == 2 || pos == p->size -1 || pos == p->size - 2)
		return (1);
	return (0);
}

void push_in_b(t_instruct *ins)
{
	int pos;

	if (ins->pb->size > 0)
	{
		pos = find_b_place(ins->pb , ins->pa->t[0]);
		if (pushing_well(ins->pb , pos))
			go_to(ins, 'b', pos);
	}
	move(ins, "pb", TRUE);
}



void push_in_a(t_instruct *ins)
{
	int pos;

	if (ins->pa->size > 0)
	{
		pos = find_a_place(ins->pa , ins->pb->t[0]);
		if (pushing_well(ins->pa , pos))
			go_to(ins, 'a', pos);
	}
	move(ins, "pa", TRUE);
}

void pivot_sorting(t_instruct *ins, int pivot, int len)
{
	int save;

//	ft_printf("PIVOT = %i\n", pivot);
	save = ins->pa->t[len];
	while (ins->pa->t[0] != save)
	{
		if (ins->pa->t[0] > pivot)
			push_in_b(ins);
		else
			move(ins, "ra", TRUE);
	}
	if (ins->pa->t[0] > pivot)
		push_in_b(ins);
	//ft_printf("LOOP OVER\n");
	go_to(ins, 'b', min_position(ins->pb));
	while (ins->pb->size > 0)
		move(ins, "pa", TRUE);

}



void quick_sort(t_instruct *ins)
{
	int pivot;

	pivot = ins->size / 2;
//	while (pivot > 2)
//	{
	pivot_sorting(ins, pivot, ins->pa->size - 1);
	//go_to(ins, 'a', n_position(ins->pa, pile_min(ins->pa)));
//	}
}

int main(int argc, char **argv)
{
	t_instruct i;

	if (init_instruction(&i, argv, argc))
	{
		i.inst_nb = 0;
		//weird_sort(&i);
		quick_sort(&i);
		if (check_option(argv, 'r'))
			ft_printf("\n%i opérations\n", i.inst_nb);
		free_instruct(&i);
	}
	return (0);
}
