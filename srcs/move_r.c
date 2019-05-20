#include "checker.h"

static void	move_r(t_pile *p)
{
	int i;
	int tmp;

	i = -1;
	tmp = p->t[0];
	while (++i < p->size)
		p->t[i] = p->t[i + 1];
	p->t[p->size - 1] = tmp; 
}

void	move_ra(t_instruct *ins)
{
	move_r(ins->a);
}

void	move_rb(t_instruct *ins)
{
	move_r(ins->b);
}

void	move_rr(t_instruct *ins)
{
	move_ra(ins);
	move_rb(ins);
}