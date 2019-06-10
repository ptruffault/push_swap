#include "checker.h"

int max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);	
}

int min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int abs(int n)
{
	return (n >= 0 ? n : -n);
}

int abs_min(int a, int b)
{
	if (abs(a) < abs(b))
		return (a);
	else
		return (b);
}

int where_to_swap(t_pile *p)
{
	int i;

	i = 0;
	while (i < p->size && ((p->t[i] < p->t[i + 1] || (p->t[i] == pile_max(p) && p->t[i + 1] == pile_min(p)))))
		i++;
	return (way_selection(p, i));
}

int find_place(t_pile *p, int val)
{
	int i;

	i = -1;
	if (val == p->t[0] - 1)
		return (0);
	while (++i < p->size)
	{
		if (p->t[i] == val + 1)
			return (i);
		if (p->t[i] == val - 1)	
			return (i + 1);
	}
	return (-1);
}


void go_forward(t_instruct *ins)
{
	if (ins->b->size > 4 && !is_already_sorted(ins->pb, FALSE)
		&& !is_already_sorted(ins->pb, FALSE))
		move(ins, where_to_swap(ins->pa) > 0 ? "rr" : "rrr" , TRUE);
	else
		move(ins, where_to_swap(ins->pa) > 0 ? "ra" : "rra" , TRUE);
}

void	finish_sort(t_instruct *ins)
{
	int m;
	int pos;

	while (ins->b->size > 0)
	{
		if ((pos = find_place(ins->pa , ins->pb->t[0])) >= 0)
		{
			m = way_selection(ins->pa , pos);
			nmove(ins, m > 0 ? "ra" : "rra", abs(m));
			move(ins, "pa" ,TRUE);
		}
		else if (ins->b->size  > 1)
			move(ins, "rb", TRUE);
		else
			move(ins, "ra", TRUE);
		
	}
	if (min_position(ins->pa) > ins->a->size / 2)
		nmove(ins, "rra", ins->a->size - min_position(ins->pa));
	else
		nmove(ins, "ra", min_position(ins->pa));	
}

void only_swap(t_instruct *ins)
{

	while (!check_sort(ins->a) || ins->b->size > 0)
	{
		if (is_already_sorted(ins->pa, TRUE))
			finish_sort(ins);
		else if (ONLY_SWAP < ins->a->size && pivot(ins->pa, ins->size))
			move(ins, "pb", TRUE);
		else if (ins->pa->t[0] > ins->pa->t[1] && !(ins->pa->t[0] == pile_max(ins->pa) && ins->pa->t[1] == pile_min(ins->pa)))
		{
			if (ins->b->size > 1 && ins->pb->t[0] < ins->pb->t[1] && !(ins->pb->t[0] == pile_min(ins->pb) && ins->pb->t[1] == pile_max(ins->pb)))
				move(ins, "ss", TRUE);
			else
				move(ins, "sa", TRUE);
		}
		else if (ins->b->size > 1 && ins->pb->t[0] < ins->pb->t[1] && !(ins->pb->t[0] == pile_min(ins->pb) && ins->pb->t[1] == pile_max(ins->pb)))
			move(ins, "sb", TRUE);
		else
			go_forward(ins);
	}
}

int main(int argc, char **argv)
{
	t_instruct i;

	if (init_instruction(&i, argv, argc))
	{
		i.inst_nb = 0;
		only_swap(&i);
		if (check_option(argv, 'r'))
			ft_printf("\n%i opérations\n", i.inst_nb);
		free_instruct(&i);
	}
	return (0);
}