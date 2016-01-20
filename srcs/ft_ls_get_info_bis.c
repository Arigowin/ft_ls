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

	size2 = 0;
	tmp = ft_itoa((rdev & MAJOR) >> 24);
	tmp2 = ft_itoa((rdev & ~MAJOR));
	if (*size < ft_strlen(tmp))
		*size = ft_strlen(tmp);
	if (size2 < ft_strlen(tmp2))
		size2 = ft_strlen(tmp2);
	elem->rdevmineur = ft_strdup(tmp);
	elem->rdevmajeur = ft_strdup(tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (size2);
}

void	ft_get_info_date(t_elem *elem, time_t mtime)
{
	elem->date = ft_strdup(ft_format_date(mtime));
	elem->sec_date = mtime;
}

void	ft_get_info_link(t_elem *elem, char *path)
{
	int		ret;
	char	buff[BUFF_SIZE];

	if ((ret = readlink(ft_strjoin(path, elem->name), buff, BUFF_SIZE)) == -1)
		ft_error(1, path);
	buff[ret] = '\0';
	elem->link = ft_strdup(buff);
}
