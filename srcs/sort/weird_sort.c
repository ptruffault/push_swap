#include "push_swap.h"


static void	finish_sort(t_instruct *ins)
{
	int m;
	int pos;

	if (max_position(ins->pb) > ins->pb->size / 2)
		nmove(ins, "rrb", ins->pb->size - max_position(ins->pb));
	else
		nmove(ins, "rb", max_position(ins->pb));
	while (ins->b->size > 0)
	{
		if ((pos = find_a_place(ins->pa , ins->pb->t[0])) >= 0)
		{
			m = way_selection(ins->pa , pos);
			nmove(ins, m > 0 ? "ra" : "rra", abs(m));
			move(ins, "pa" ,TRUE);
		}
		else if (ins->b->size  > 1)
			move(ins, "rb", TRUE);
	}
	if (min_position(ins->pa) > ins->a->size / 2)
		nmove(ins, "rra", ins->a->size - min_position(ins->pa));
	else
		nmove(ins, "ra", min_position(ins->pa));
}

void weird_sort(t_instruct *ins)
{
	int m;
	int pos;

	while (!check_sort(ins->a) || ins->b->size > 0)
	{
		if (is_already_sorted(ins->pa, TRUE))
			finish_sort(ins);
		else if (pivot(ins->pa->t[0], ins->size))
		{
			if ((pos = find_b_place(ins->pb , ins->pa->t[0])) > 0)
			{
				m = way_selection(ins->pb , pos);
				nmove(ins, m > 0 ? "rb" : "rrb", abs(m));
			}
			move(ins, "pb" ,TRUE);
		}
		else if (!pivot(ins->pa->t[0], ins->size) && !pivot(ins->pa->t[1], ins->size) 
			&& ins->pa->t[0] > ins->pa->t[1] && !(ins->pa->t[0] == pile_max(ins->pa) && ins->pa->t[1] == pile_min(ins->pa)))
			move(ins, "sa", TRUE);
		else if (!all_pushed(ins))
			move(ins, where_to_push(ins->pa, ins->size) > 0 ? "ra" : "rra", TRUE);
		else
			move(ins, where_to_swap(ins->pa) > 0 ? "ra" : "rra" , TRUE);	
	}
}
