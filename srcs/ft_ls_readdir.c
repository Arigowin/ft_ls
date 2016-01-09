#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdio.h>
static char		**ft_readdir_bis(DIR *dir)
{
	struct dirent	*dp;
	char			*tmp;
	char			**lst;
	int				i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_readdir_bis\n");
#endif

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

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_readdir\n");
#endif

	dir = opendir(fpath);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
			ft_putendl(path);
		ft_error(1, path);
	}
	else
	{
		lst = ft_readdir_bis(dir);
		closedir(dir);
		return (lst);
	}
	return (NULL);
}

int		ft_is_dir(char *path, char *fpath)
{
	struct stat b;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_is_dir\n");
#endif

	if (lstat(fpath, &b) == -1)
	{
		if (errno == ENOTDIR)
			return (0);
		ft_error(1, path);
	}
	if (S_ISDIR (b.st_mode))
		return (1);
	else
		return (0);
}
