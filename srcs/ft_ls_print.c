#include "ft_ls.h"
#include "libft.h"

#include <stdio.h>
void			ft_printone1(t_elem *elem, size_t *size)
{
	size_t		i;

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
}

void			ft_printone2(t_elem *elem, size_t *size, int rdev)
{
	size_t		i;
	size_t		t;

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
}

void			ft_printone3(t_elem *elem)
{
	ft_putstr(" ");
	ft_putstr(elem->date);
	ft_putstr(" ");
	ft_putstr(elem->name);
	if (elem->link != NULL)
	{
		ft_putstr(" -> ");
		ft_putstr(elem->link);
	}
}

static void		ft_printone(t_elem *elem, size_t *size, int rdev, int op_l)
{
	// DEBUG
#ifdef DEBUG
	printf("DEBUG : printone\n");
#endif

	if (op_l)
	{
		ft_printone1(elem, size);
		ft_printone2(elem, size, rdev);
		ft_printone3(elem);
		ft_putstr("\n");
	}
	else
		ft_putendl(elem->name);
}

static void		ft_print_while(t_elem **elem, t_ft_ls data, int t)
{
	t_elem	*tmp;

	tmp = *elem;
	while (tmp)
	{
		if ((data.op_a || tmp->name[0] != '.' || !t) && tmp->name != NULL)
		{
			if (data.sizemax[4] == 0)
				ft_printone(tmp, data.sizemax, 0, data.op_l);
			else
				ft_printone(tmp, data.sizemax, 1, data.op_l);
		}
		tmp = tmp->next;
	}
}

void			ft_print(t_ft_ls data, t_elem **elem, char t)
{
	// DEBUG
#ifdef DEBUG
	printf("DEBUG : print\n");
#endif

	// condition a ajouter mais je ne sais pas encore laquelle
	// pas afficher si dossier vide
	if (data.op_l && t)
	{
		ft_putstr("total ");
		ft_putnbrendl(data.total);
	}
	ft_print_while(elem, data, t);
}
