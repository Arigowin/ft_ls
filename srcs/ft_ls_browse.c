#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>
#include <dirent.h>

#include <stdio.h>
static int		ft_browse_recu(t_ft_ls data, char *path, int i)
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

	tmp = NULL;
	tmp2 = NULL;
	j = 0;
	if (data.nb_path > 1 || (data.op_recu && i > 0))
	{
		if (i > 0)
			ft_putendl("");
		ft_putstr(path);
		ft_putendl(":");
	}
	fpath = ft_format_path(path);
	if ((elem = ft_readdir(fpath, path, data)) == NULL)
		return (0);
	j = 0;
	while (j < elem[0].nbelem)
	{
		if (data.op_a || elem[j].name[0] != '.')
		{
			if (data.op_l)
			{
				ft_print(data, &elem, fpath);
				break ;
			}
			else
				ft_putendl(elem[j].name);
		}
		j++;
	}
	ft_strdel(&fpath);
	j = 0;
	while (j < elem[0].nbelem && data.op_recu)
	{
		if ((data.op_a || elem[j].name[0] != '.')
				&& ft_strcmp(elem[j].name, "..") != 0
				&& ft_strcmp(elem[j].name, ".") != 0)
		{
			if (elem[j].type == DT_DIR)
			{
				if (path[ft_strlen(path) - 1] == '/')
					tmp = ft_strdup(path);
				else
					tmp = ft_strproperjoin(path, "/");
				tmp2 = ft_strproperjoin(tmp, elem[j].name);
				ft_browse_recu(data, tmp2, i + 1);
			}
		}
		j++;
	}
	return (0);
}

void	ft_browse(t_ft_ls *data)
{
	int		i;
	int		j;
	t_elem	*elem;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_browse\n");
#endif

	if ((elem = (t_elem *)malloc(sizeof(t_elem) * data->nb_path)) == NULL)
		exit (ft_error(1, "ft_browse"));
	i = 0;
	j = 0;
	while (i < data->nb_path)
	{
		if (ft_is_dir(data->path[i]) == 0)
		{
			if (data->op_l)
			{
				ft_init_t_elem(&(elem[j]));
				elem[j].name = ft_strdup(data->path[i]);
				elem[0].nbelem++;
			}
			else
				ft_putendl(data->path[i]);
			ft_strdel(&(data->path[i]));
			j++;
		}
		i++;
	}
	if (data->op_l && elem[0].name != NULL)
		ft_print(*data, &elem, "./");
	i = 0;
	while (i < data->nb_path)
	{
		if (data->path[i] != NULL)
			ft_browse_recu(*data, ft_strdup(data->path[i]), i);
		i++;
	}
}
