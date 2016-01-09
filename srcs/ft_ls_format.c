#include "ft_ls.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#include <stdio.h>
char			*ft_format_path(char *str)
{
	char	*path;
	char	*tmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_path\n");
#endif

	if ((str[0] != '/' && str[1] != '/') && (str[0] != '.'))
	{
		if ((tmp = ft_strjoin("./", str)) == NULL)
			exit(ft_error(1, str));
		ft_strdel(&str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	path = ft_strdup(str);
	if (path[ft_strlen(path) - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		ft_strdel(&path);
		path = ft_strjoin(tmp, "/");
		free(tmp);
	}
	if (ft_is_dir(str, path) == 0)
	{
		free(path);
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

	tmp = ctime(&(date));
	ret = ft_strsub(tmp, 4, 12);
	return (ret);
}
