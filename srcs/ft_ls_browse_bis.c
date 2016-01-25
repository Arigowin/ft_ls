/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_browse_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 17:55:05 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 17:55:06 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static int		ft_browse_read(t_ft_ls *data, char **path, int i, t_elem **elem)
{
	char	*fpath;
	int		nb;

	if (data->nb_path > 1 || (data->op_recu && i > 0))
	{
		if (i > 0)
			ft_putendl("");
		ft_putstr(*path);
		ft_putendl(":");
	}
	fpath = ft_format_path(*path);
	nb = 0;
	if ((*elem = ft_readdir(fpath, *path, data, &nb)) == NULL)
		return (0);
	ft_print(data, elem, 1, nb);
	ft_strdel(&fpath);
	return (1);
}

static void		ft_browse_recu_bis(t_ft_ls *d, t_elem *tmpel, char *path, int i)
{
	char	*tmp;
	char	*tmp2;

	if ((d->op_a || tmpel->name[0] != '.')
			&& ft_strcmp(tmpel->name, "..") != 0
			&& ft_strcmp(tmpel->name, ".") != 0)
	{
		if (tmpel->droit[0] == 'd')
		{
			if (path[ft_strlen(path) - 1] == '/')
				tmp = ft_strdup(path);
			else
				tmp = ft_strjoin(path, "/");
			tmp2 = ft_strjoin(tmp, tmpel->name);
			ft_strdel(&tmp);
			ft_browse_recu(d, tmp2, i + 1);
			ft_strdel(&tmp2);
		}
	}
}

int				ft_browse_recu(t_ft_ls *data, char *path, int i)
{
	t_elem	*elem;
	t_elem	*tmpel;

	if (ft_browse_read(data, &path, i, &elem) == 0)
		return (0);
	tmpel = elem;
	while (tmpel && data->op_recu)
	{
		ft_browse_recu_bis(data, tmpel, path, i);
		tmpel = tmpel->next;
	}
	ft_free_elem(&elem, data->op_l, data->op_t);
	return (0);
}
