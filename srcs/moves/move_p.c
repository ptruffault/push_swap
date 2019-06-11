#include "checker.h"

static void	push(t_pile *p, int value)
{
	int i;

	i = ++p->size;
	while (--i > 0)
		p->t[i] = p->t[i - 1];
	p->t[0] = value;
}

static void	remove_first(t_pile *p)
{
	int i;

	i = -1;
	if (p->size > 0)
	{
		while (++i < p->size - 1)
			p->t[i] = p->t[i + 1];
		p->size--;
	}
}

void		move_pa(t_instruct *ins)
{
	if (ins->b->size > 0)
	{
		push(ins->a, ins->b->t[0]);
		remove_first(ins->b);
		if (ins->pb)
		{
			push(ins->pa, ins->pb->t[0]);
			remove_first(ins->pb);
		}
	}
}

void		move_pb(t_instruct *ins)
{
	if (ins->a->size > 0)
	{
		push(ins->b, ins->a->t[0]);
		remove_first(ins->a);
		if (ins->pa)
		{
			push(ins->pb, ins->pa->t[0]);
			remove_first(ins->pa);
		}
	}
}
