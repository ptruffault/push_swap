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
	int 		size;
	int 		inst_nb;
	t_pile		*a;
	t_pile		*b;
	t_pile		*pa;
	t_pile		*pb;
}				t_instruct;

typedef struct	s_moves
{
	void		(*fct)(struct s_insruct *i);
	char		*op;
}				t_moves;

int 	check_option(char **argv, char option);
int		check_sort(t_pile *p);

void	clear_term(void);
void 	puttab(t_instruct *ins);
void 	putpile(t_instruct *i, char *op);

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

int		nmove(t_instruct *ins, char *op , int n);
int 	instruct_loop(t_instruct *ins, t_bool affichage);
int		move(t_instruct *ins, char *op, t_bool affichage);

t_pile *init_pile_a(char **argv);
t_pile *init_pile_b(int size);
int		init_instruction(t_instruct *ins, char **argv, int argc);
void	free_instruct(t_instruct *ins);
t_pile	*free_pile(t_pile *p);
#endif
