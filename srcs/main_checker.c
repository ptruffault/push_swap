#include "checker.h"

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
		ft_putendl(check_sort(i.a) && !i.b->size ? "OK" : "KO");
		free_instruct(&i);
	}
	return (0);
}

