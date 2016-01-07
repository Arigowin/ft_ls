#include "ft_ls.h"
# include "libft.h"
# include <dirent.h>
# include <sys/errno.h>
# include <stdlib.h>

static char		**ft_readdir_bis(DIR *dir)
{
	struct dirent	*dp;
	char			*tmp;
	char			**lst;
	int				i;

	tmp = NULL;
	i = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (tmp == NULL)
			tmp = ft_strdup(dp->d_name);
		else
		{
			tmp = ft_strjoin(tmp, "\n");
			tmp = ft_strjoin(tmp, dp->d_name);
		}
		i++;
	}
	lst = ft_strsplit(tmp, '\n');
	ft_sort_str(&lst, i);
	return (lst);
}

char			**ft_readdir(char *fpath, char *path)
{
	DIR				*dir;
	char			**lst;

	dir = opendir(fpath);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			ft_putendl(path);
			exit (0);
		}
		ft_error("1");
	}
	else
	{
		lst = ft_readdir_bis(dir);
		closedir(dir);
		return (lst);
	}
	return (NULL);
}
