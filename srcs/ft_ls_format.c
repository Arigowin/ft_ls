#include "ft_ls.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#include <stdio.h>
char			*ft_format_path(char *str)
{
	char	*path;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_path\n");
#endif

	if ((str[0] != '/' && str[1] != '/') && (str[0] != '.'))
	{
		str = ft_strproperjoin(ft_strdup("./"), str);
	}
	path = ft_strdup(str);
	if (path[ft_strlen(path) - 1] != '/')
	{
		path = ft_strproperjoin(path, ft_strdup("/"));
	}
	if (ft_is_dir(str, path) == 0)
	{
		ft_strdel(&path);
		return (str);
	}
	return (path);
}

char			*ft_format_date(time_t date)
{
	char *ret;
	char *tmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_date\n");
#endif

	tmp = ft_strdup(ctime(&(date)));
	ret = ft_strsub(tmp, 4, 12);
	ft_strdel(&tmp);
	return (ret);
}
