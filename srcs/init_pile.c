#include "checker.h"

static int 	is_valid_arg(char *arg)
{
	int i;

	i = arg[0] == '-' ? 0 : -1;
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (0);
	return (1);
}

static t_pile *check_doublon(t_pile *ret)
{
	int i;
	int j;

	i = -1;
	while (++i < ret->size)
	{
		j = i;
		while (++j < ret->size)
			if (ret->t[i] == ret->t[j])
				return (free_pile(ret));
	}
	return (ret);
}


t_pile	*free_pile(t_pile *p)
{
	if (p)
	{
		free(p->t);
		free(p);
	}
	return (NULL);
}

t_pile *init_pile_a(char **argv)
{
	t_pile *ret;
	int i;

	if (!(ret = (t_pile *)malloc(sizeof(t_pile))))
		return (NULL);
	ret->size = ft_strarrlen(argv);
	i = -1;
	while (argv[++i])
		if (*argv[i] == '-' && ft_strchr("ar", argv[i][1]))
			ret->size--;
	if (!(ret->t = (int *)malloc(sizeof(int) * ret->size)))
		return (free_pile(ret));
	i = -1;
	while (++i < ret->size)
		if (is_valid_arg(argv[i]))
			ret->t[i] = ft_atoi(argv[i]);
		else if (*argv[i] != '-' && !ft_strchr("ar", argv[i][1]))
			return (free_pile(ret));
	return (check_doublon(ret));
}

t_pile *init_pile_b(int size)
{
	t_pile *ret;

	if (!(ret = (t_pile *)malloc(sizeof(t_pile))))
		return (NULL);
	if (!(ret->t = (int *)malloc(sizeof(int) * size)))
		return (free_pile(ret));
	ret->size = 0;
	return (ret);
}