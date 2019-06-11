/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_places.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 23:33:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/06/10 23:33:52 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>



/*
int find_place(t_pile *p, int val)
{
	int i;
	i = 0;

	if (p->t[i] > val && val > p->t[p->size - 1])
		return (0);
	if (val < pile_min(p))
		return (min_position(p));
	while (++i <= p->size)
	{
		if (p->t[i - 1] < val)
		{
			if (val < p->t[i])
				return (i);
			if (p->t[i] == pile_max(p) && val > p->t[i])
				return (i + 1);
		}
	}
	return (-1);
}*/



int main(void)
{
	int t[5] = {20, 15, 10, 5, 0};



	printf("-> %i\n", 	find_place(t, -2
		));

}
