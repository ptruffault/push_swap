#include "checker.h"

static int	usage(char *ar)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(ar, 2);
	ft_putstr_fd(" [number list]", 2);
	return (0);
}


static int	init_position(t_instruct *ins)
{
	int i;
	int j;
	int position;

	i = -1;
	if (!(ins->pa = (t_pile *)malloc(sizeof(t_pile)))
		|| !(ins->pb = (t_pile *)malloc(sizeof(t_pile))))
		return (0);
	if (!(ins->pa->t = (int *)malloc(sizeof(int) * ins->a->size))
			|| !(ins->pb->t = (int *)malloc(sizeof(int) * ins->a->size)))
	{
		free_pile(ins->pa);
		free_pile(ins->pb);
		return (0);
	}
	ins->pa->size = ins->a->size;
	while (++i < ins->a->size)
	{
		j = -1;
		position = 0;
		while (++j < ins->a->size)
			if (ins->a->t[i] > ins->a->t[j])
				position++;
		ins->pa->t[i] = position;
	}
	return (1);
}

void		free_instruct(t_instruct *ins)
{
	free_pile(ins->a);
	free_pile(ins->b);
	free_pile(ins->pa);
	free_pile(ins->pb);
}

int			init_instruction(t_instruct *ins, char **argv, int argc)
{
	if (argc > 1)
	{
		ins->a = NULL;
		ins->b = NULL;
		ins->pa = NULL;
		ins->pb = NULL;
		if (!(ins->a = init_pile_a(&argv[1]))
			|| !(ins->b = init_pile_b(ins->a->size))
			|| !init_position(ins))
		{
			ft_putendl_fd("Error", 2);
			free_instruct(ins);
			return (0);
		}
		ins->size = ins->a->size;
	}
	else
		return (usage(argv[0]));
	return (1);
}