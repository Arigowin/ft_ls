/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_readdir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:25 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/28 12:48:30 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <sys/stat.h>

static t_elem	*ft_readdir_bis(DIR *dir, t_ft_ls *data, char *path, int *nb)
{
	struct dirent	*dp;
	t_elem			*elem;
	t_elem			*new;
	int				tmp;

	elem = NULL;
	new = NULL;
	while ((dp = readdir(dir)) != NULL)
	{
		new = ft_elem_new(dp->d_name);
		if ((tmp = ft_get_info(path, new, data)) == -1)
			continue ;
		data->total += tmp;
		ft_elem_insert(&elem, new, data->op_r, data->op_t);
		new = new->next;
		(*nb)++;
	}
	if (dp == NULL && elem == NULL)
		ft_error(1, "ft_read_bis");
	return (elem);
}

t_elem			*ft_readdir(char *fpath, char *path, t_ft_ls *data, int *nb)
{
	DIR				*dir;
	t_elem			*elem;

	if ((dir = opendir(fpath)) == NULL)
	{
		if (errno == ENOENT || errno == ENOTDIR)
		{
			if (ft_is_dir(path) != 0)
			{
				ft_putendl(ft_strsub(path, 2, ft_strlen(path)));
				return (NULL);
			}
		}
		ft_error(1, path);
		return (NULL);
	}
	elem = ft_readdir_bis(dir, data, fpath, nb);
	closedir(dir);
	return (elem);
}

int				ft_is_dir(char *path)
{
	struct stat b;

	if (stat(path, &b) == -1)
	{
		if (lstat(path, &b) == -1)
		{
			if (errno == ENOTDIR)
				return (0);
			return (ft_error(1, path));
		}
	}
	if (S_ISDIR(b.st_mode))
		return (1);
	else if (S_ISLNK(b.st_mode))
		return (2);
	return (0);
}
