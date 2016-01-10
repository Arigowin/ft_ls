#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdio.h>
static t_elem		*ft_readdir_bis(DIR *dir)
{
	struct dirent	*dp;
	char			*tmp;
	char			*tmp2;
	char			**lst;
	char			**lst2;
	char			tmpc;
	int				i;
	int				j;
	t_elem			*elem;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_readdir_bis\n");
#endif

	tmp = NULL;
	i = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (tmp == NULL)
		{
			tmp = ft_strdup(dp->d_name);
			tmpc = ((char)dp->d_type != 0 ? (char)dp->d_type : 42);
			tmp2 = ft_strdup(&tmpc);
		}
		else
		{
			tmp = ft_strjoin(tmp, "\n");
			tmp = ft_strjoin(tmp, dp->d_name);
			tmp2 = ft_strjoin(tmp2, ":");
			tmpc = ((char)dp->d_type != 0 ? (char)dp->d_type : 42);
			tmp2 = ft_strjoin(tmp2, &tmpc);
		}
		i++;
	}
	if (dp == NULL && tmp == NULL)
		ft_error(1, "ft_read_bis");
	lst = ft_strsplit(tmp, '\n');
	lst2 = ft_strsplit(tmp2, ':');
	if ((elem = (t_elem *)malloc(sizeof(t_elem) * i)) == NULL)
		exit (ft_error(1, "ft_readdir_bis"));
	j = 0;
	while (lst[j])
	{
		ft_init_t_elem(&(elem[j]));
		elem[j].name = lst[j];
		elem[j].type = lst2[j][0];
		elem[j].nbelem = i;
		j++;
	}
	ft_sort_elem(&elem, elem[0].nbelem);
	return (elem);
}

t_elem			*ft_readdir(char *fpath, char *path)
{
	DIR				*dir;
	t_elem			*elem;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_readdir\n");
#endif

	dir = opendir(fpath);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
			ft_putendl(path);
		ft_error(1, ft_strsub(path, 2, ft_strlen(path)));
	}
	else
	{
		elem = ft_readdir_bis(dir);
		closedir(dir);
		return (elem);
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
	return (S_ISDIR (b.st_mode));
}
