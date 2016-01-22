#include "ft_ls.h"
# include "libft.h"
#include <stdlib.h>

#include <stdio.h>
static void		ft_swap_s(char **s1, char **s2)
{
	char	*tmp;

	tmp = ft_strdup(*s1);
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
	ft_strdel(s2);
	*s2 = ft_strdup(tmp);
	free(tmp);
}

void			ft_sort_str(char ***str, int size, char r)
{
	int		i;
	int		x;
	int		cmp;

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
			cmp = (r ? ft_strcmp((*str)[x], (*str)[i]) :
					ft_strcmp((*str)[i], (*str)[x]));
			if (cmp < 0)
				ft_swap_s(&((*str)[x]), &((*str)[i]));
			i++;
		}
		x++;
		i = x;
	}
}
