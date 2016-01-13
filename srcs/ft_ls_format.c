#include "ft_ls.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#include <stdio.h>
char			*ft_format_path(char *str)
{
	char	*tmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_path\n");
#endif

	if ((str[0] != '/' || str[1] != '/') && (str[0] != '.'))
	{
		tmp = ft_strjoin(ft_strdup("./"), str);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (ft_is_dir(str) == 0)
		return (str);
	return (ft_strjoin(str, ft_strdup("/")));
}

char			*ft_format_date(time_t date)
{
	char *ret;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_date\n");
#endif

	ret = ft_strsub(ctime(&(date)), 4, 12);
	return (ret);
}
