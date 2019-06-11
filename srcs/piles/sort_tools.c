#include "checker.h"

int max_position(t_pile *p)
{
	int i;

	i = -1;
	while (++i < p->size)
		if (p->t[i] == pile_max(p))
			return (i);
	return (-1);
}

int min_position(t_pile *p)
{
	int i;

	i = -1;
	while (++i < p->size)
		if (p->t[i] == pile_min(p))
			return (i);
	return (-1);
}

int n_position(t_pile *p, int n)
{
	int i;

	i = -1;
	if (n > pile_max(p))
		return (max_position(p));
	else if (n < pile_min(p))
		return (min_position(p));
	while (++i < p->size)
		if (p->t[i] == n)
			return (i);
	return (-1);	
}

int way_selection(t_pile *p, int i)
{
	if (i < 0)
		return (i);
	if (i <= p->size / 2)
		return (i);
	else
		return (-(p->size -  i)); 
}

int pivot(t_pile *p, int total)
{
	if (total < 3)
		return (0);
	else if (total < 6 && p->t[0] < total / 2 - p->size / 4)
		return (1);
	else if (total < 15 && p->t[0] < total / 2)
		return (1);
	else if (total < 30 && p->t[0] <= 2 * total / 3)
		return (1);
	else if (total >= 30 && p->t[0] <= 4 * total / 5)
		return (1);
	return (0);
}
