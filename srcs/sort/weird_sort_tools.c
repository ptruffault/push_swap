#include "push_swap.h"

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
