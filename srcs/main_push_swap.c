#include "push_swap.h"

int main(int argc, char **argv)
{
	t_instruct i;

	if (init_instruction(&i, argv, argc))
	{
		i.inst_nb = 0;
		weird_sort(&i);
		if (check_option(argv, 'r'))
			ft_printf("\n%i opérations\n", i.inst_nb);
		free_instruct(&i);
	}
	return (0);
}
