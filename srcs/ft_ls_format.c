#include "ft_ls.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#include <stdio.h>
char			*ft_format_path(char *str)
{
	char	*tmp;
	int		ret;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_path\n");
#endif

	if ((str[0] != '/' && str[1] != '/') && (str[0] != '.'))
	{
		tmp = ft_strjoin(ft_strdup("./"), str);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if ((ret =ft_is_dir(str)) == 0)
		return (str);
	tmp = ft_strdup("/");
	str = ft_strjoin(str, tmp);
	return (str);
}

static char		*future(time_t date)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	ret = ft_strsub(ctime(&(date)), 4, 7);
	if (date > 253402297199)
	{
		tmp = ft_strsub(ctime(&(date)), 19, 10);
		tmp = ft_strsplit(tmp, ' ')[0];
		tmp2 = ft_strdup(" ");
		tmp2 = ft_strjoin(tmp2, tmp);
	}
	else
		tmp = ft_strsub(ctime(&(date)), 19, 5);
	ret = ft_strjoin(ret, tmp);
	return (ret);
}

char			*ft_format_date(time_t date)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	time_t	sdate;
	time_t	now;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_date\n");
#endif

	sdate = date;
	now = time(&date);
	tmp = ctime(&(sdate));
	if (sdate > now)
		ret = future(sdate);
	else if (sdate < now - ((365 / 2) * (3600 * 24)))
	{
		ret = ft_strsub(tmp, 4, 7);
		tmp2 = ft_strsub(tmp, 19, 5);
		ret = ft_strjoin(ret, tmp2);
	}
	else
		ret = ft_strsub(tmp, 4, 12);
	return (ret);
}
