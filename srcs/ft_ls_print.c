#include "ft_ls.h"
#include "libft.h"

#include <stdio.h>
static void		ft_printone(t_elem *elem, size_t *size, int rdev, int op_l)
{
	size_t	i;
	size_t	t;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : printone\n");
#endif

	if (op_l)
	{
		ft_putstr(elem->droit);
		ft_putstr("  ");
		i = -1;
		while (++i < size[0] - ft_strlen(elem->nlink))
			ft_putchar(' ');
		ft_putstr(elem->nlink);
		ft_putstr(" ");
		ft_putstr(elem->uid);
		i = -1;
		while (++i < size[1] - ft_strlen(elem->uid))
			ft_putchar(' ');
		ft_putstr("  ");
		ft_putstr(elem->grp);
		i = -1;
		while (++i < size[2] - ft_strlen(elem->grp))
			ft_putchar(' ');
		ft_putstr("  ");
		if (elem->size != NULL)
		{
			i = -1;
			t = (rdev ? size[4] + size[3] + 2 : size[3] - ft_strlen(elem->size));
			while (++i < t)
				ft_putchar(' ');
			ft_putstr(elem->size);
		}
		else
		{
			ft_putstr(" ");
			i = -1;
			while (++i < size[3] - ft_strlen(elem->rdevmineur))
				ft_putchar(' ');
			ft_putstr(elem->rdevmineur);
			ft_putstr(", ");
			i = -1;
			while (++i < (size[4] - ft_strlen(elem->rdevmajeur)))
				ft_putchar(' ');
			ft_putstr(elem->rdevmajeur);
		}
		ft_putstr(" ");
		ft_putstr(elem->date);
		ft_putstr(" ");
		ft_putstr(elem->name);
		if (elem->link != NULL)
		{
			ft_putstr(" -> ");
			ft_putstr(elem->link);
		}
		ft_putstr("\n");
	}
	else
		ft_putendl(elem->name);
}

#include <stdlib.h>
void	ft_print(t_ft_ls data, t_elem **elem, char *path, int t)
{
	t_elem		*tmp;
	size_t		sizemax[5] = {0, 0, 0, 0, 0};
	size_t		total;
	int			i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : print\n");
#endif

	exit(1); ///////////////////////////////////////
	total = 0;
	i = 0;
	tmp = *elem;
	while (tmp)
	{
		if (tmp->name != NULL && (data.op_a || tmp->name[0] != '.'))
			total += ft_get_info(path, tmp, sizemax);
		i++;
		tmp = tmp->next;
	}
	// condition a ajouter mais je ne sais pas encore laquelle
	if (data.op_l && t && (i > 2 || data.op_a))
	{
		ft_putstr("total ");
		ft_putnbrendl(total);
	}
//	if (data.op_t)
//		ft_sort_tmp_date(tmp, tmp.nbelem, data.op_r, data.op_a);
	tmp = *elem;
	while (tmp)
	{
		if ((data.op_a || tmp->name[0] != '.') && tmp->name != NULL)
		{
			if (sizemax[4] == 0)
				ft_printone(tmp, sizemax, 0, data.op_l);
			else
				ft_printone(tmp, sizemax, 1, data.op_l);
		}
		tmp = tmp->next;
	}
}
