#include "checker.h"

static void move_r(t_pile *p)
{
	int i;
	int tmp;

	i = p->size;
	tmp = p->t[i - 1];
	while (--i > 0)
		p->t[i] = p->t[i - 1];
	p->t[0] = tmp;
}

void	move_rra(t_instruct *ins)
{
	move_r(ins->a);
	move_r(ins->pa);
}

void	move_rrb(t_instruct *ins)
{
	move_r(ins->b);
	move_r(ins->pb);
}

void	move_rrr(t_instruct *ins)
{
	move_rra(ins);
	move_rrb(ins);
}
