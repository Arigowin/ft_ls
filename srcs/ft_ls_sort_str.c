#include "ft_ls.h"
# include "libft.h"

void	ft_swap_s(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strdup(*s2);
	*s2 = ft_strdup(tmp);
}

void	ft_sort_str(char ***str, int size)
{
	int		i;
	int		x;
	int		cmp;

	i = 0;
	x = 0;
	size--;
	if ((cmp = ft_strcmp((*str)[0], (*str)[size])) > 0)
	{
		ft_swap_s(&((*str)[0]), &((*str)[size]));
	}
	while (x != size + 1)
	{
		while (i < size)
		{
			if ((cmp = ft_strcmp((*str)[i], (*str)[i + 1])) > 0)
			{
				ft_swap_s(&((*str)[i]), &((*str)[i + 1]));
			}
			i++;
		}
		x++;
		i = 0;
	}
}
