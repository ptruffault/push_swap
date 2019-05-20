#include "checker.h"

static const t_moves	g_moves[] = {
	{move_sa, "sa"},
	{move_sb,"sb"},
	{move_ss,"ss"},
	{move_pa,"pa"},
	{move_pb,"pb"},
	{move_ra,"ra"},
	{move_rb,"rb"},
	{move_rr,"rr"},
	{move_rra,"rra"},
	{move_rrb,"rrb"},
	{move_rrr,"rrr"},
	{0, 0}
};

void	instruct_loop(t_instruct *ins)
{
	char 	**op;
	int		i;
	int 	j;
	int 	done;

	j = -1;
	done = 1;
	if ((op = ft_get_txt(0)))
	{
		while (done && op[++j])
		{
			i = -1;
			done = 0;
			while (!done && g_moves[++i].op)
			{
				if (ft_strequ(op[j], g_moves[i].op))
				{
					done = 1;
					g_moves[i].fct(ins);
					ft_printf("\n%s DONE\n", g_moves[i].op);
					putpile(ins);
				}
			}
			if (!done)
				error("invalid operator", op[j]);
		}
		ft_freestrarr(op);
	}
}


int	check_sort(t_instruct *ins)
{
	int i;

	i = -1;
	if (ins->b->size > 0)
		return (0);
	while (++i < (int)ins->a->size - 1)
		if (ins->a->t[i] > ins->a->t[i + 1])
			return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_instruct i;

	if (argc > 1)
	{
		if ((i.a = init_pile_a(&argv[1])))
		{
			if ((i.b = init_pile_b(i.a->size)))
			{
				instruct_loop(&i);
				ft_putendl(check_sort(&i) ? "OK" : "KO");
				free_pile(i.b);
			}
			free_pile(i.a);
		}
		else
			ft_putendl_fd("Error", 2);
	}
	else
		ft_putendl_fd("Usage : ./checker [number] (...)", 2);
	return (0);
}

