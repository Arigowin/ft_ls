#include "ft_ls.h"
#include "libft.h"

#include <stdio.h>
static int		ft_browse_recu(t_ft_ls data, char *path)
{
	char	**lst;
	char	*fpath;
	int j;

	j = 0;
	fpath = ft_format_path(path);
	if (ft_is_dir(path, fpath) == 1)
	{
		if (data.nb_path > 1 || ft_strchr(data.op, 'R') != NULL)
		{
			ft_putendl("");
			ft_putstr(path);
			ft_putendl(":");
		}
		if ((lst = ft_readdir(fpath, path)) == NULL)
			return (0);
		while (lst[j] != NULL)
		{
			if (ft_strchr(data.op, 'l') == NULL)
			ft_putendl(lst[j]);
			else
				printinfo(fpath, lst[j]);
			j++;
		}
		j = 0;
		while (lst[j] != NULL)
		{
			if (lst[j][0] != '.' && ft_strchr(data.op, 'R') != NULL)
			{
				if (ft_is_dir(lst[j], ft_strjoin(fpath, lst[j])) == 1)
					ft_browse_recu(data, ft_strjoin(ft_strjoin(path, "/"), lst[j]));
			}
			j++;
		}
	}
	else
	{
		ft_putendl("");
		ft_putendl(path);
	}
	return (0);
}

void	ft_browse(t_ft_ls data)
{
	int		i;

	i = 0;
	while (i < data.nb_path)
	{
		ft_browse_recu(data, data.path[i]);
		i++;
	}
}
