/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:14 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 16:55:49 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

size_t	ft_get_info(char *path, t_elem *elem, t_ft_ls *data)
{
	struct stat	st;
	char		*tmp2;

	tmp2 = ft_strjoin(path, elem->name);
	if (lstat(tmp2, &st) == -1)
		return (ft_error(1, elem->name));
	elem->droit = ft_modeoffile(st.st_mode);
	ft_get_info_date(elem, st.st_mtime);
	if ((data->op_a || elem->name[0] != '.') && data->op_l)
	{
		data->size[0] = ft_get_info_nlink(elem, st.st_nlink, data->size[0]);
		data->size[1] = ft_get_info_pw(elem, st.st_uid, data->size[1]);
		data->size[2] = ft_get_info_gr(elem, st.st_gid, data->size[2]);
		if (elem->droit[0] != 'c' && elem->droit[0] != 'b')
			data->size[3] = ft_get_info_size(elem, st.st_size, data->size[3]);
		else
			data->size[4] = ft_get_infordev(elem, st.st_size, &(data->size[3]));
		if (elem->droit[0] == 'l')
			ft_get_info_link(elem, path);
	}
	free(tmp2);
	if (elem->name[0] != '.' || data->op_a)
		return (st.st_blocks);
	else
		return (0);
}

int		ft_get_info_nlink(t_elem *elem, nlink_t nlink, size_t size)
{
	char	*tmp;
	size_t	ltmp;

	tmp = ft_itoa(nlink);
	ltmp = ft_strlen(tmp);
	if (size < ltmp)
		size = ltmp;
	elem->nlink = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int		ft_get_info_pw(t_elem *elem, uid_t uid, size_t size)
{
	struct passwd	*pw;
	char			*tmp;
	size_t			ltmp;

	if ((pw = getpwuid(uid)) == NULL)
		tmp = ft_itoa(uid);
	else
		tmp = ft_strdup(pw->pw_name);
	ltmp = ft_strlen(tmp);
	if (size < ltmp)
		size = ltmp;
	elem->uid = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int		ft_get_info_gr(t_elem *elem, gid_t gid, size_t size)
{
	struct group	*gr;
	char			*tmp;
	size_t			ltmp;

	if ((gr = getgrgid(gid)) == NULL)
		tmp = ft_itoa(gid);
	else
		tmp = ft_strdup(gr->gr_name);
	ltmp = ft_strlen(tmp);
	if (size < ltmp)
		size = ltmp;
	elem->grp = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int		ft_get_info_size(t_elem *elem, off_t s, size_t size)
{
	char	*tmp;
	size_t	ltmp;

	tmp = ft_itoa(s);
	ltmp = ft_strlen(tmp);
	if (size < ltmp)
		size = ltmp;
	elem->size = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}
