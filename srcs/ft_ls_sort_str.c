#include "ft_ls.h"

void ft_sort_str(char ***str, int size)
{
	int		i;
	int		cmp;
	char	*tmp;

	i = 0;
	if ((cmp = ft_strcmp((*str)[0], (*str)[size])) > 0)
	{
		tmp = (*str)[0];
		ft_strdel(&((*str)[0]));
		(*str)[0] = ft_strdup((*str)[size]);
		ft_strdel(&((*str)[size]));
		(*str)[size] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	while (i < size)
	{
		if ((cmp = ft_strcmp((*str)[i], (*str)[i + 1])) > 0)
		{
			tmp = (*str)[i];
			ft_strdel(&((*str)[i]));
			(*str)[i] = ft_strdup((*str)[i + 1]);
			ft_strdel(&((*str)[i + 1]));
			(*str)[i + 1] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
}
