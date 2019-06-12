#ifndef 	PUSH_SWAP_H
# define	 PUSH_SWAP_H
# include 	"libft.h"
# include 	"checker.h"

# define LIM_MIN 3
# define LIM_LOW 6 
# define LIM_MID 10
# define LIM_UP 16

int pile_max(t_pile *p);
int pile_min(t_pile *p);
int min_position(t_pile *p);
int max_position(t_pile *p);

int pivot(int val, int total);
int way_selection(t_pile *p, int i);
int n_position(t_pile *p, int n);
int is_already_sorted(t_pile *p, t_bool croissan);
int find_b_place(t_pile *p, int val);
int where_to_swap(t_pile *p);
int where_to_push(t_pile *p, int total_size);
int all_pushed(t_instruct *ins);
int find_a_place(t_pile *p, int val);
void weird_sort(t_instruct *ins);

int abs(int n);
int max(int a, int b);
int min(int a, int b);
#endif