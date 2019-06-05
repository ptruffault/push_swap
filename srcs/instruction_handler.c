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

int	move(t_instruct *ins, char *op, t_bool affichage)
{
	int i;

	i = -1;
	while (g_moves[++i].op)
	{
		if (ft_strequ(op, g_moves[i].op))
		{
			g_moves[i].fct(ins);
			if (affichage)
				ft_putendl(op);
			return (1);
		}
	}
	error("invalid operator", op);
	return (0);
}

int	nmove(t_instruct *ins, char *op , int n)
{
	int i;

	i = -1;
	while (++i < n)
		if (!move(ins, op, TRUE))
			return (0);
	return (i);
}

void	instruct_loop(t_instruct *ins, t_bool affichage)
{
	char 	**op;
	int 	j;
	j = -1;
	if ((op = ft_get_txt(0)))
	{
		while (op[++j])
		{
			if (affichage)
				putpile(ins, op[j]);
			if (!move(ins, op[j], FALSE))
				break;
		}
		ft_freestrarr(op);
	}
}
