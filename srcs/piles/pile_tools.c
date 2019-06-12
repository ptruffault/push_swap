#include "push_swap.h"

int pile_max(t_pile *p)
{
	int ret;
	int i;

	i = -1;
	ret = p->t[0];
	while (++i < p->size)
		if (p->t[i] > ret)
			ret = p->t[i];
	return (ret);
}

int pile_min(t_pile *p)
{
	int ret;
	int i;

	i = -1;
	ret = p->t[0];
	while (++i < p->size)
		if (p->t[i] < ret)
			ret = p->t[i];
	return (ret);
}

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
	while (++i < p->size)
		if (p->t[i] == n)
			return (i);
	return (-1);	
}
