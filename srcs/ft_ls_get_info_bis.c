#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int		ft_get_info_rdev(t_elem *elem, dev_t rdev, size_t *size)
{
	char	*tmp;
	char	*tmp2;
	size_t	size2;
	size_t	ltmp;

	size2 = 0;
	tmp = ft_itoa((rdev & MAJOR) >> 24);
	tmp2 = ft_itoa((rdev & ~MAJOR));
	ltmp = ft_strlen(tmp);
	if (*size < ltmp)
		*size = ltmp;
	ltmp = ft_strlen(tmp2);
	if (size2 < ltmp)
		size2 = ltmp;
	elem->rdevmineur = ft_strdup(tmp);
	elem->rdevmajeur = ft_strdup(tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (size2);
}

void	ft_get_info_date(t_elem *elem, time_t mtime)
{
	elem->date = ft_format_date(mtime);
	elem->sec_date = mtime;
}

void	ft_get_info_link(t_elem *elem, char *path)
{
	int		ret;
	char	buff[BUFF_SIZE];
	char	*tmp;

	tmp = ft_strjoin(path, elem->name);
	if ((ret = readlink(tmp, buff, BUFF_SIZE)) == -1)
		ft_error(1, path);
	buff[ret] = '\0';
	elem->link = ft_strdup(buff);
	ft_strdel(&tmp);
}
