#include "ft_ls.h"

char	**ft_readdir(char *path)
{
	struct dirent	*dp;
	DIR				*dir;
	int				i;
	char			*tmp;
	char			**lst;

	if (path == NULL)
		dir = opendir(".");
	else
		dir = opendir(path);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			printf("%s\n", path);
			exit (0);
		}
		exit (ft_error(NULL));
	}
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
	closedir(dir);
	lst = ft_strsplit(tmp, '\n');
	ft_sort_str(&lst, i);
	return (lst);
}
