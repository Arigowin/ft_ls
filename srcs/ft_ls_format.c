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
	return (ft_strjoin(str, ft_strdup("/")));
}

static char		*future(time_t date)
{
	char *ret;
	char *tmp;

	ret = ft_strsub(ctime(&(date)), 4, 7);
	if (date > 253402297199)
	{
		tmp = ft_strsub(ctime(&(date)), 19, 10);
		tmp = ft_strsplit(tmp, ' ')[0];
		tmp = ft_strjoin(" ", tmp);
	}
	else
		tmp = ft_strsub(ctime(&(date)), 19, 5);
	ret = ft_strjoin(ret, tmp);
	return (ret);
}

char			*ft_format_date(time_t date)
{
	char *ret;
	char *tmp;
	time_t sdate;
	time_t now;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_format_date\n");
#endif

	sdate = date;
	now = time(&date);
	if (sdate > now)
	{
		ret = future(sdate);
	}
	else if (sdate < now - (365 * ((3600 * 24)) / 2))
	{
		ret = ft_strsub(ctime(&(sdate)), 4, 7);
		tmp = ft_strsub(ctime(&(sdate)), 19, 5);
		ret = ft_strjoin(ret, tmp);
	}
	else
		ret = ft_strsub(ctime(&(sdate)), 4, 12);
	return (ret);
}
