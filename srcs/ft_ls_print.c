#include "ft_ls.h"
#include "libft.h"

#include <stdio.h>
static void		ft_printone(t_elem elem, size_t *size, int rdev, int op_l)
{
	size_t	i;
	size_t	t;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : printone\n");
#endif

	if (op_l)
	{
		ft_putstr(elem.droit);
		ft_putstr("  ");
		i = -1;
		while (++i < size[0] - ft_strlen(elem.nlink))
			ft_putchar(' ');
		ft_putstr(elem.nlink);
		ft_putstr(" ");
		ft_putstr(elem.uid);
		i = -1;
		while (++i < size[1] - ft_strlen(elem.uid))
			ft_putchar(' ');
		ft_putstr("  ");
		ft_putstr(elem.grp);
		i = -1;
		while (++i < size[2] - ft_strlen(elem.grp))
			ft_putchar(' ');
		ft_putstr("  ");
		if (elem.size != NULL)
		{
			i = -1;
			t = (rdev ? size[4] + size[3] + 2 : size[3] - ft_strlen(elem.size));
			while (++i < t)
				ft_putchar(' ');
			ft_putstr(elem.size);
		}
		else
		{
			ft_putstr(" ");
			i = -1;
			while (++i < size[3] - ft_strlen(elem.rdevmineur))
				ft_putchar(' ');
			ft_putstr(elem.rdevmineur);
			ft_putstr(", ");
			i = -1;
			while (++i < (size[4] - ft_strlen(elem.rdevmajeur)))
				ft_putchar(' ');
			ft_putstr(elem.rdevmajeur);
		}
		ft_putstr(" ");
		ft_putstr(elem.date);
		ft_putstr(" ");
		ft_putstr(elem.name);
		if (elem.link != NULL)
		{
			ft_putstr(" -> ");
			ft_putstr(elem.link);
		}
		ft_putstr("\n");
	}
	else
		ft_putendl(elem.name);
}

void	ft_print(t_ft_ls data, t_elem **elem, char *path)
{
	int			i;
	size_t		sizemax[5] = {0, 0, 0, 0, 0};
	size_t		total;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : print\n");
#endif

	i = 0;
	total = 0;
	while (i < (*elem)[0].nbelem)
	{
		if ((*elem)[i].name != NULL && (data.op_a || (*elem)[i].name[0] != '.'))
			total += ft_get_info(path, &((*elem)[i]), sizemax);
		i++;
	}
	i = 0;
	// condition a ajouter mais je ne sais pas encore laquelle
	if (data.op_l)
	{
		ft_putstr("total ");
		ft_putnbrendl(total);
	}
	ft_sort_elem(elem, (*elem)[0].nbelem, data.op_r);
	if (data.op_t)
		ft_sort_elem_date(elem, (*elem)[0].nbelem, data.op_r, data.op_a);
	while (i < (*elem)[0].nbelem)
	{
		if ((data.op_a || (*elem)[i].name[0] != '.') && (*elem)[i].name != NULL)
		{
			if ((*elem)[i].rdevmineur == NULL)
				ft_printone((*elem)[i], sizemax, 0, data.op_l);
			else
				ft_printone((*elem)[i], sizemax, 1, data.op_l);
		}
		i++;
	}
}
