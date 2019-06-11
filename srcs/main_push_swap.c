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


int find_a_place(t_pile *p, int val)
{
	int i;

	i = 0;
	if (p->t[p->size - 1] < val && val < p->t[0])
		return (0);
	if (val < pile_min(p))
		return (min_position(p));
	if (val > pile_max(p))
		return (max_position(p));
	while (++i <= p->size)
	{
		if (p->t[i - 1] < val)
		{
			if (val < p->t[i])
				return (i);
			if (p->t[i] == pile_max(p) && val > p->t[i])
				return (i + 1);
		}
	}
	return (-1);
}

int find_b_place(t_pile *p, int val)
{
	int i;

	i = 0;
	if (p->t[0] < val && val < p->t[p->size - 1])
		return (0);
	if (val < pile_min(p))
		return (min_position(p) + 1);
	if (val > pile_max(p))
		return (max_position(p));
	while (++i <= p->size)
		if (p->t[i] < val && val < p->t[i - 1])
				return (i);
	return (-1);
}


int where_to_swap(t_pile *p)
{
	int i;
	int j;

	i = 0;
	j = p->size;
	while (i < p->size && ((p->t[i] < p->t[i + 1] || (p->t[i] == pile_max(p) && p->t[i + 1] == pile_min(p)))))
		i++;
	while (j > 0 && (p->t[j] > p->t[j - 1] || (p->t[j] == pile_min(p) && p->t[j - 1] == pile_max(p))))
		j--;
	if (j > 0)
		j--;
	//ft_printf("WHERE TO SWAP i = %i j = %i  --> %i  by %i\n", i, p->size - j, i > p->size - j ? j : i, way_selection(p, i > p->size - j ? j : i));
	return (way_selection(p, 0 > p->size - j - 1 && i > p->size - j - 1 ? j : i));
}

int where_to_push(t_pile *p, int total_size)
{
	int i;
	int j;

	i = 0;
	j = p->size;
	while (i < p->size && !pivot(p->t[i], total_size))
		i++;
	while (j > 0 && !pivot(p->t[j], total_size))
		j--;

	//ft_printf("WHERE TO PUSH i = %i j = %i\n--> %i   by %i", i, j, i > p->size - j ? j : i, way_selection(p, i > p->size - j ? j : i));
	return (way_selection(p, i > p->size - j ? j : i));
}

int all_pushed(t_instruct *ins)
{
	int i;

	if (ins->size < 3)
		return (1);
	i = -1;
	while (++i < ins->pa->size)
		if (pivot(ins->pa->t[i], ins->size))
			return (0);
	return (1);
}


void go_forward(t_instruct *ins)
{
/*	*/
	if (!all_pushed(ins))
	{
		move(ins, where_to_push(ins->pa, ins->size) > 0 ? "ra" : "rra", TRUE);
	}
	else
	{
		move(ins, where_to_swap(ins->pa) > 0 ? "ra" : "rra" , TRUE);	
	}

}

void	finish_sort(t_instruct *ins)
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

void only_swap(t_instruct *ins)
{
	int m;
	int pos;

	while (!check_sort(ins->a) || ins->b->size > 0)
	{
		if (is_already_sorted(ins->pa, TRUE))
			finish_sort(ins);
		else if (pivot(ins->pa->t[0], ins->size))
		{
			pos = find_b_place(ins->pb , ins->pa->t[0]);
			if (pos > 0)
			{
				m = way_selection(ins->pb , pos);
				nmove(ins, m > 0 ? "rb" : "rrb", abs(m));
			}
			//ft_printf("HERE I AM\n m = %i\n", m);
			
			move(ins, "pb" ,TRUE);
		}
		else if (!pivot(ins->pa->t[0], ins->size) && !pivot(ins->pa->t[1], ins->size) && ins->pa->t[0] > ins->pa->t[1] && !(ins->pa->t[0] == pile_max(ins->pa) && ins->pa->t[1] == pile_min(ins->pa)))
		{
			move(ins, "sa", TRUE);
		}
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



























