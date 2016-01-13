#include "ft_ls.h"
# include "libft.h"
#include <stdlib.h>

#include <stdio.h>
static void		ft_swap_e(t_elem *e1, t_elem *e2)
{
	t_elem	tmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_swap_e\n");
#endif

	tmp = *e1;
	*e1 = *e2;
	*e2 = tmp;
}

void			ft_sort_elem(t_elem **elem, int size, int r)
{
	int		i;
	int		x;
	int		cmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_sort_elem\n");
#endif

	i = 1;
	x = 0;
	size--;
	while (x <= size)
	{
		while (i <= size)
		{
			cmp = (r ? ft_strcmp((*elem)[x].name, (*elem)[i].name) :
					ft_strcmp((*elem)[i].name, (*elem)[x].name));
			if (cmp < 0)
				ft_swap_e(&((*elem)[x]), &((*elem)[i]));
			i++;
		}
		x++;
		i = x;
	}
}

void			ft_sort_elem_date(t_elem **elem, int size, int r, int a)
{
	int		i;
	int		x;
	int		cmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_sort_elem_date\n");
#endif

	i = 1;
	x = 0;
	size--;
	while (x <= size)
	{
		while (i <= size)
		{
			if (a || ((*elem)[i].name[0] != '.' && (*elem)[x].name[0] != '.'))
			{
				cmp = (r ? (*elem)[i].sec_date - (*elem)[x].sec_date :
						(*elem)[x].sec_date - (*elem)[i].sec_date);
				if (cmp < 0)
					ft_swap_e(&((*elem)[x]), &((*elem)[i]));
			}
			i++;
		}
		x++;
		i = x;
	}
}

static void		ft_swap_s(char **s1, char **s2)
{
	char	*tmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_swap_s\n");
#endif

	tmp = ft_strdup(*s1);
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
	ft_strdel(s2);
	*s2 = ft_strdup(tmp);
	free(tmp);
}

void			ft_sort_str(char ***str, int size, int r)
{
	int		i;
	int		x;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_sort_str\n");
#endif

	i = 0;
	x = 0;
	size--;
	while (x <= size)
	{
		while (i <= size)
		{
			if (r)
			{
				if ((ft_strcmp((*str)[x], (*str)[i])) < 0)
					ft_swap_s(&((*str)[x]), &((*str)[i]));
			}
			else
				if ((ft_strcmp((*str)[x], (*str)[i])) > 0)
					ft_swap_s(&((*str)[x]), &((*str)[i]));
			i++;
		}
		x++;
		i = x;
	}
}
