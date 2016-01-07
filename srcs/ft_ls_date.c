#include "ft_ls.h"
# include "libft.h"
# include <time.h>

char	*ft_format_date(time_t date)
{
	char **d;
	char **h;
	char *ret;
	char *tmp;

	tmp = ctime(&(date));
	ret = ft_strnew(ft_strlen(tmp));
	d = ft_strsplit(tmp, ' ');
	h = ft_strsplit(d[3], ':');

	ret = ft_strcat(ret, d[1]);
	ret = ft_strcat(ret, " ");
	ret = ft_strcat(ret, d[2]);
	ret = ft_strcat(ret, " ");
	ret = ft_strcat(ret, h[0]);
	ret = ft_strcat(ret, ":");
	ret = ft_strcat(ret, h[1]);
	return (ret);
}
