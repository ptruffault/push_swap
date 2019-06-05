#include "checker.h"

int pile_max(t_pile *p)
{
	int ret;
	int i;

	i = -1;
	ret = p->t[0];
	while (++i < p->size)
		if (p->t[i] > ret)
			ret = p->t[i];
	return (ret);

}

int pile_min(t_pile *p)
{
	int ret;
	int i;

	i = -1;
	ret = p->t[0];
	while (++i < p->size)
		if (p->t[i] < ret)
			ret = p->t[i];
	return (ret);
}
