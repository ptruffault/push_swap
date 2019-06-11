#include "checker.h"

static int 	is_valid_arg(char *arg)
{
	int i;

	if (!arg)	
		return (0);
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

int init_tab(char **argv, t_pile *ret)
{
	char **arr;
	int k;
	int i;
	int j;

	i = -1;
	k = -1;
	i = -1;
	while (argv[++i])
	{
		if (*argv[i] == '-' && ft_isalpha(argv[i][1]) && !ft_strchr("ar", argv[i][1]))
		{
			error_c("invalid options", argv[i][1]);
			ret->size--;
			return (0);
		}
		else if (is_valid_arg(argv[i]))
			ret->t[++k] = ft_atoi(argv[i]);
		else if (argv[i] && (arr = ft_strsplit(argv[i], ' '))
			&& *arr && (ret->t = ft_realloc(ret->t, ret->size * sizeof(int)
			, (ret->size + ft_strarrlen(arr)) * sizeof(int))))
		{
			j = -1;
			ret->size--;
			while (arr[++j])
			{
				if (is_valid_arg(arr[j]))
				{
					ret->size++;
					ret->t[++k] = ft_atoi(arr[j]);
				}
			}
			ft_freestrarr(arr);
		}
	}
	return (1);
}

t_pile *init_pile_a(char **argv)
{
	t_pile *ret;

	if (!(ret = (t_pile *)malloc(sizeof(t_pile))))
		return (NULL);
	ret->size = ft_strarrlen(argv);
	if (!(ret->t = (int *)malloc(sizeof(int) * ret->size))
		|| !init_tab(argv, ret))
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
