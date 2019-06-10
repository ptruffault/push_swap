#include "checker.h"
#include <termcap.h>
#include <unistd.h>

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


void 	puttab(t_instruct *ins)
{
	int i;

	i = 0;

	ft_printf("A(%i)  B(%i)\n", ins->a->size, ins->b->size);
	while (i < ins->a->size || i < ins->b->size)
	{
		if (i < ins->a->size)
			ft_printf(" |%i| ", ins->pa->t[i]);
		else
			ft_putstr(" ... ");
		if (i < ins->b->size)
			ft_printf(" |%i|\n", ins->pb->t[i]);
		else
			ft_putstr(" ...\n");
		i++;
	}
}

void	clear_term(void)
{
	char buf[1024];

	tgetent(buf, getenv("TERM"));
	ft_putstr(tgetstr("cl", NULL));
}

void 	putpile(t_instruct *ins, char *op)
{
	int i;

	i = 0;
	ft_putstr("\n\n\n");
	while (i < ins->pa->size || i < ins->pb->size)
	{
		if (i < ins->pa->size)
		{
			ft_putstr(S_VERT);
			ft_putnchar('#', ins->pa->t[i] + 1);
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
			else if (ft_strequ(op, "ra") || ft_strequ(op, "rr"))
				ft_putstr(" ↑   ");
			else if (ft_strequ(op, "rra") || ft_strequ(op, "rrr"))
				ft_putstr(" ↓   ");
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
			else if (ft_strequ(op, "rb") || ft_strequ(op, "rr"))
				ft_putstr("↑    ");
			else if (ft_strequ(op, "rrb") || ft_strequ(op, "rrr"))
				ft_putstr("↓    ");
			else
				ft_putstr("     ");
			ft_putstr(S_BLEU);
			ft_putnchar('#',  ins->pb->t[i] + 1);
			ft_putstr(NORMAL);
		}
		ft_putchar('\n');
		i++;
	}
	if (op)
	{
		ft_putnchar(' ', pile_max(ins->pa) + 5);
		ft_printf("%s%s%s\n", ROUGE, op, NORMAL);
	}
}