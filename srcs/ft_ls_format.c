#include "ft_ls.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

char			*ft_format_path(char *str)
{
	char	*path;

	if ((str[0] != '/' && str[1] != '/') && (str[0] != '.'))
	{
		if ((str = ft_strjoin("./", str)) == NULL)
			exit(ft_error(str));
	}
	path = ft_strdup(str);
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	if (ft_is_dir(str, path) == 0)
		return (str);
	return (path);
}

char	*ft_format_date(time_t date)
{
	char *ret;
	char *tmp;

	tmp = ctime(&(date));
	ret = ft_strsub(tmp, 4, 12);
	return (ret);
}
