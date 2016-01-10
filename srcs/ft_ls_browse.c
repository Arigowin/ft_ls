#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/dirent.h>

#include <stdio.h>
static int		ft_browse_recu(t_ft_ls data, char *path)
{
	t_elem	*elem;
	char	*fpath;
	char	*tmp;
	char	*tmp2;
	int		j;

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
		if (data.nb_path > 1 || data.op_R)
		{
			ft_putendl("");
			ft_putstr(path);
			ft_putendl(":");
		}
		if ((elem = ft_readdir(fpath, path)) == NULL)
			return (0);
		j = 0;
		while (j < elem[0].nbelem)
		{
			if (data.op_a || elem[j].name[0] != '.')
			{
				if (data.op_l)
				{
					print(data, &elem, fpath);
					break ;
				}
				else
					ft_putendl(elem[j].name);
			}
			j++;
		}
		j = 0;
		while (j < elem[0].nbelem)
		{
			if (data.op_R && elem[j].name[0] != '.')
			{
				if (elem[j].type == DT_DIR)
				{
					if (path[ft_strlen(path) - 1] == '/')
						tmp = ft_strdup(path);
					else
						tmp = ft_strjoin(path, "/");
					tmp2 = ft_strjoin(tmp, elem[j].name);
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
//		if (data.op_l)
//			print(elem, path);
//		else
//			ft_putendl(path);
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
