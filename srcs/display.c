#include "checker.h"

void 	putpile(t_instruct *ins)
{
	int i;

	i = 0;

	ft_printf("    A(%i)  B(%i)\n", ins->a->size, ins->b->size);
	while (i < ins->a->size || i < ins->b->size)
	{
		ft_printf("[%i]", i);
		if (i < ins->a->size)
			ft_printf(" |%i|(%i) ", ins->a->t[i], ins->pa->t[i]);
		else
			ft_putstr(" ... ");
		if (i < ins->b->size)
			ft_printf(" |%i|(%i)\n", ins->b->t[i],ins->pb->t[i]);
		else
			ft_putstr(" ...\n");
		i++;
	}
}