#ifndef CHECKER_H
# define CHECKER_H
#include "libft.h"

typedef struct	s_pile
{
	int			*t;
	int			size;
}				t_pile;

typedef struct	s_insruct
{
	t_pile		*a;
	t_pile		*b;
}				t_instruct;

typedef struct	s_moves
{
	void		(*fct)(struct s_insruct *i);
	char		*op;
}				t_moves;


//display
void 	putpile(t_instruct *i);

//moves fonctions
void	move_sa(t_instruct *i);
void	move_sb(t_instruct *i);
void	move_ss(t_instruct *i);
void	move_pa(t_instruct *i);
void	move_pb(t_instruct *i);
void	move_ra(t_instruct *i);
void	move_rb(t_instruct *i);
void	move_rr(t_instruct *i);
void	move_rra(t_instruct *i);
void	move_rrb(t_instruct *i);
void	move_rrr(t_instruct *i);

t_pile *init_pile_a(char **argv);
t_pile *init_pile_b(int size);
t_pile	*free_pile(t_pile *p);
#endif
