#include "checker.h"

int main(int argc, char **argv)
{
	t_instruct i;

	if (init_instruction(&i, argv, argc))
	{
		instruct_loop(&i, TRUE);
		ft_putendl(check_sort(&i) ? "OK" : "KO");
		free_instruct(&i);
	}
	return (0);
}

