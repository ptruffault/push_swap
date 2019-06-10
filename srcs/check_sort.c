#include "checker.h"

int	check_sort(t_pile *p)
{
	int i;

	i = -1;
	while (++i < p->size - 1)
		if (p->t[i] > p->t[i + 1])
			return (0);
	return (1);
}


int is_already_sorted(t_pile *p, t_bool croissan)
{
	int i;

	i = -1;
	while (++i < p->size - 1)
		if ((croissan == TRUE && p->t[i] > p->t[i + 1] && p->t[i] != pile_min(p))
			|| (croissan == FALSE && p->t[i] < p->t[i + 1] && p->t[i + 1] != pile_max(p)))
			return (0);
	return (1);
}

int check_option(char **argv, char option)
{
	int i;

	i = -1;
	while (argv[++i])
		if (*argv[i] == '-' && ft_strchr(argv[i], option))
			return (1);
	return (0);
}
