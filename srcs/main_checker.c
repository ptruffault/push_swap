#include "checker.h"
#include <termcap.h>

int main(int argc, char **argv)
{
	t_instruct i;
	char buf[1024];

	 tgetent(buf, getenv("TERM"));
	if (init_instruction(&i, argv, argc))
	{
		instruct_loop(&i, TRUE);
		ft_putendl(check_sort(&i) ? "OK" : "KO");
		free_instruct(&i);
	}
	return (0);
}

