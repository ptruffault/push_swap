#include "checker.h"

static void	move_s(t_pile *p)
{
	int tmp;

	if (p->size >= 2)
	{
		tmp = p->t[1];
		p->t[1] = p->t[0];
		p->t[0] = tmp;
	}	
}

void	move_sa(t_instruct *i)
{
	move_s(i->a);
}

void	move_sb(t_instruct *i)
{
	move_s(i->b);
}

void	move_ss(t_instruct *i)
{
	move_sa(i);
	move_sb(i);
}