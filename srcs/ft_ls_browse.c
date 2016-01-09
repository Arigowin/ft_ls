#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
static int		ft_browse_recu(t_ft_ls data, char *path)
{
	char	**lst;
	char	*fpath;
	char *tmp;
	char *tmp2;
	int j;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_browse_recu\n");
#endif

	j = 0;
	fpath = ft_strdup(path);
	if (ft_is_dir(path, fpath) == 1)
	{
		free(fpath);
		fpath = ft_format_path(path);
		if (data.nb_path > 1 || ft_strchr(data.op, 'R') != NULL)
		{
			ft_putendl("");
			ft_putstr(path);
			ft_putendl(":");
		}
		if ((lst = ft_readdir(fpath, path)) == NULL)
			return (0);
		j = 0;
		while (lst[j] != NULL)
		{
			if (ft_strchr(data.op, 'a') || lst[j][0] != '.')
			{
				if (ft_strchr(data.op, 'l') == NULL)
					ft_putendl(lst[j]);
				else
					printinfo(fpath, lst[j]);
			}
			j++;
		}
		j = 0;
		while (lst[j] != NULL)
		{
			if (lst[j][0] != '.' && ft_strchr(data.op, 'R') != NULL)
			{
				if (ft_is_dir(lst[j], ft_strjoin(fpath, lst[j])) == 1)
				{
					if (path[ft_strlen(path) - 1] == '/')
						tmp = ft_strdup(path);
					else
						tmp = ft_strjoin(path, "/");
					tmp2 = ft_strjoin(tmp, lst[j]);
					free(tmp);
					ft_browse_recu(data, tmp2);
					free(tmp2);
				}
			}
			j++;
		}
	}
	else
	{
		ft_putendl("");
		if (ft_strchr(data.op, 'l') == NULL)
			ft_putendl(path);
		else
			printinfo(fpath, "");
	}
	free(fpath);
	return (0);
}

void	ft_browse(t_ft_ls data)
{
	int		i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_browse\n");
#endif

	i = 0;
	while (i < data.nb_path)
	{
		ft_browse_recu(data, data.path[i]);
		i++;
	}
}
