#include "checker.h"
#include <termcap.h>
#include <unistd.h>

void 	putpile_tab(t_instruct *ins)
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

static void	ft_putnchar(char c, int n)
{
	while (n-- > 0)
		ft_putchar(c);
}

void	ft_putnstr(char *s, int n)
{
	while (n-- > 0)
		ft_putstr(s);	
}


void 	putpile(t_instruct *ins, char *op)
{
	char buf[1024];
	int i;

	i = 0;
	tgetent(buf, getenv("TERM"));
	ft_putstr(tgetstr("cl", NULL));
	while (i < ins->pa->size || i < ins->pb->size)
	{
		if (i < ins->pa->size)
		{
			ft_putstr(S_VERT);
			ft_putnchar(ins->pa->t[i] + 32, ins->pa->t[i] + 1);
			ft_putstr(NORMAL);
			ft_putnchar(' ', pile_max(ins->pa) - ins->pa->t[i] + 2);
			ft_putstr(ROUGE);
			if (i == 0 && (ft_strequ(op, "sa") || ft_strequ(op, "ss")))
				ft_putstr("←═╗  ");
			else if (i == 1 &&  (ft_strequ(op, "sa") || ft_strequ(op, "ss")))
				ft_putstr("←═╝  ");
			else if (ft_strequ(op, "pa") && i == 0)
				ft_putstr("←════");
			else if (ft_strequ(op, "pb") && i == 0)
				ft_putstr("════→");
			else if (i == 0 && (ft_strequ(op, "ra") || ft_strequ(op, "rr")))
				ft_putstr(" ↑   ");
			else if (i == ins->a->size - 1 && (ft_strequ(op, "rra") || ft_strequ(op, "rrr")))
				ft_putstr(" ↓   ");
			else if (ft_strequ(op, "rra") || ft_strequ(op, "rrr") 
		 		|| ft_strequ(op, "ra") || ft_strequ(op, "rr"))
				ft_putstr(" ║   ");
			else
				ft_putstr("     ");
			ft_putstr(NORMAL);
		}
		else
			ft_putnchar(' ', pile_max(ins->pa) + 8);
		if (i < ins->pb->size)
		{
			ft_putstr(ROUGE);
			if (i == 0 && (ft_strequ(op, "sb") || ft_strequ(op, "ss")))
				ft_putstr("╔═→  ");
			else if (i == 1 &&  (ft_strequ(op, "sb") || ft_strequ(op, "ss")))
				ft_putstr("╚═→  ");
			else if (i == 0 && (ft_strequ(op, "rb") || ft_strequ(op, "rr")))
				ft_putstr("↑    ");
			else if (i == ins->b->size - 1 && (ft_strequ(op, "rrb") || ft_strequ(op, "rrr")))
				ft_putstr("↓    ");
			else if (ft_strequ(op, "rrb") || ft_strequ(op, "rrr")
				|| ft_strequ(op, "rb") || ft_strequ(op, "rr"))
				ft_putstr("║    ");
			else
				ft_putstr("     ");
			ft_putstr(S_BLEU);
			ft_putnchar(ins->pa->t[i] + 32,  ins->pb->t[i] + 1);
			ft_putstr(NORMAL);
		}
		ft_putchar('\n');
		i++;
	}
	if (op)
		ft_printf("           %s\n\n", op);
	if (!check_sort(ins))
		sleep(1);
}