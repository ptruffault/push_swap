#include "checker.h"

int check_option(char **argv, char option)
{
	int i;

	i = -1;
	while (argv[++i])
		if (*argv[i] == '-' && ft_strchr(argv[i], option))
			return (1);
	return (0);
}


// options : -a -> affichage des piles à chaque opération
//			 -r -> affichage du résultat
int main(int argc, char **argv)
{
	t_instruct i;
	int inb;

	if (init_instruction(&i, argv, argc))
	{
		inb = instruct_loop(&i, check_option(argv, 'a') ? TRUE : FALSE);
		if (check_option(argv, 'r'))
		{
			putpile(&i, NULL);
			ft_printf("→ %i\n", inb);
		}
		ft_putendl(check_sort(&i) ? "OK" : "KO");
		free_instruct(&i);
	}
	return (0);
}

