#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>
#include <dirent.h>
#include <sys/errno.h>

#include <stdio.h>
#include <unistd.h>
static int		ft_browse_read(t_ft_ls data, char **path, int i, t_elem **elem)
{
	char	*fpath;

	if (data.nb_path > 1 || (data.op_recu && i > 0))
	{
		if (i > 0)
			ft_putendl("");
		ft_putstr(*path);
		ft_putendl(":");
	}
	fpath = ft_format_path(*path);
	if ((*elem = ft_readdir(fpath, *path, &data)) == NULL)
		return (0);
	ft_print(data, elem, 1);
	ft_strdel(&fpath);
	return (1);
}

static int		ft_browse_recu(t_ft_ls data, char *path, int i)
{
	t_elem	*elem;
	t_elem	*tmpel;
	char	*tmp;
	char	*tmp2;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_browse_recu\n");
#endif

	if (ft_browse_read(data, &path, i, &elem) == 0)
		return (0);
	tmpel = elem;
	while (tmpel && data.op_recu)
	{
		if ((data.op_a || tmpel->name[0] != '.')
				&& ft_strcmp(tmpel->name, "..") != 0
				&& ft_strcmp(tmpel->name, ".") != 0)
		{
			if (tmpel->type == DT_DIR)
			{
				if (path[ft_strlen(path) - 1] == '/')
					tmp = ft_strdup(path);
				else
					tmp = ft_strjoin(path, "/");
				tmp2 = ft_strjoin(tmp, tmpel->name);
				ft_strdel(&tmp);
				ft_browse_recu(data, tmp2, i + 1);
				ft_strdel(&tmp2);
			}
		}
		tmpel = tmpel->next;
	}
	ft_free_elem(&elem, data.op_l, data.op_t);
	return (0);
}

static int		ft_browse_not_a_directorie(t_ft_ls *data, t_elem *elem)
{
	t_elem	*new;
	int		i;
	int		j;
	int		er;

	i = 0;
	j = 0;
	while (i < data->nb_path)
	{
		if (((er = ft_is_dir(data->path[i])) == 0 && er != -1) ||
				(er == 2 && data->op_l))
		{
			new = ft_elem_new(data->path[i]);
			if (data->op_l || data->op_t)
				data->total += ft_get_info("./", new, data);
			ft_elem_insert(&elem, new, data->op_r, data->op_t);
			ft_strdel(&(data->path[i]));
			j++;
		}
	   if (er == -1)
		   ft_strdel(&(data->path[i]));
	   i++;
	}
	if (elem && j != 0)
		ft_print(*data, &elem, 0);
	ft_free_elem(&elem, data->op_l, data->op_t);
	return (j);
}

void			ft_browse(t_ft_ls *data)
{
	t_elem	*elem;
	int		i;
	int		j;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_browse\n");
#endif

	elem = NULL;
	j = ft_browse_not_a_directorie(data, elem);
	i = 0;
	while (i < data->nb_path)
	{
		if (data->path[i] != NULL)
			ft_browse_recu(*data, ft_strdup(data->path[i]), i + j);
		i++;
	}
}
