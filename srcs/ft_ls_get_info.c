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
	{
		ft_error(1, elem->name);
		return (0);
	}
	if (data->op_t && !data->op_l)
		ft_get_info_date(elem, st.st_mtime);
	else
	{
		ft_strdel(&tmp2);
		elem->droit = ft_modeoffile(st.st_mode);
		data->sizemax[0] = ft_get_info_nlink(elem, st.st_nlink, data->sizemax[0]);
		data->sizemax[1] = ft_get_info_pw(elem, st.st_uid, data->sizemax[1]);
		data->sizemax[2] = ft_get_info_gr(elem, st.st_gid, data->sizemax[2]);
		if (elem->droit[0] != 'c' && elem->droit[0] != 'b')
			data->sizemax[3] = ft_get_info_size(elem, st.st_size, data->sizemax[3]);
		else
			data->sizemax[4] = ft_get_info_rdev(elem, st.st_size, &(data->sizemax[3]));
		ft_get_info_date(elem, st.st_mtime);
		if (elem->droit[0] == 'l')
			ft_get_info_link(elem, path);
	}
	return (st.st_blocks);
}

int		ft_get_info_nlink(t_elem *elem, nlink_t nlink, size_t size)
{
	char *tmp;

	tmp = ft_itoa(nlink);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	elem->nlink = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int		ft_get_info_pw(t_elem *elem, uid_t uid, size_t size)
{
	struct passwd	*pw;
	char			*tmp;

	if ((pw = getpwuid(uid)) == NULL)
		tmp = ft_itoa(uid);
	else
		tmp = ft_strdup(pw->pw_name);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	elem->uid = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int		ft_get_info_gr(t_elem *elem, gid_t gid, size_t size)
{
	struct group	*gr;
	char			*tmp;

	if ((gr = getgrgid(gid)) == NULL)
		tmp = ft_itoa(gid);
	else
		tmp = ft_strdup(gr->gr_name);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	elem->grp = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int		ft_get_info_size(t_elem *elem, off_t s, size_t size)
{
	char *tmp;

	tmp = ft_itoa(s);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	elem->size = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}
