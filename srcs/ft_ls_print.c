#include "ft_ls.h"
#include "libft.h"

void			ft_printone1(t_elem *elem, size_t *size)
{
	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : printone1\n");
#endif

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
	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : printone2\n");
#endif

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

void			ft_printone3(t_elem *elem, )
{
	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : printone3\n");
#endif

	ft_putstr(" ");
	ft_putstr(elem->date);
	ft_putstr(" ");
	if (elem->droit[0] == 'l')
		ft_putstr_color(PURPLE, elem->name);
	else if (elem->droit[0] == 'd')
		ft_putstr_color(CYAN, elem->name);
	else if (ft_strchr(elem->droit, 'x') != NULL)
		ft_putstr_color(GREEN, elem->name);
	else
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
	ft_putstr("DEBUG : printone\n");
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
	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : print_while\n");
#endif

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

void			ft_print(t_ft_ls *data, t_elem **elem, char t, int nb)
{
	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : print\n");
#endif

	// condition a ajouter mais je ne sais pas encore laquelle
	// pas afficher si dossier vide
	if (data->op_l && t && (nb > 2 || data->op_a))
	{
		ft_putstr("total ");
		ft_putnbrendl(data->total);
		data->total = 0;
	}
	ft_print_while(elem, *data, t);
	data->sizemax[0] = 0;
	data->sizemax[1] = 0;
	data->sizemax[2] = 0;
	data->sizemax[3] = 0;
	data->sizemax[4] = 0;
}
