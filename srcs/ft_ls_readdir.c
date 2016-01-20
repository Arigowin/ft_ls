#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdio.h>
static t_elem		*ft_readdir_bis(DIR *dir, char r)
{
	struct dirent	*dp;
	t_elem			*elem;
	t_elem			*tmp;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_readdir_bis\n");
#endif

	
	elem = NULL;
	tmp = NULL;
	while ((dp = readdir(dir)) != NULL)
	{
		tmp = ft_elem_insert(&elem, dp->d_name, r);
		tmp->type = ((char)dp->d_type != 0 ? (char)dp->d_type : 42);
		// ajouter stat ici ??????????????????????
	}
	if (dp == NULL && elem == NULL)
		ft_error(1, "ft_read_bis");
	return (elem);
}

t_elem			*ft_readdir(char *fpath, char *path, char r)
{
	DIR				*dir;
	t_elem			*elem;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_readdir\n");
#endif

	if ((dir = opendir(fpath)) == NULL)
	{
		if (ft_is_dir(path) != 0 && (errno == ENOENT || errno == ENOTDIR))
		{
			ft_putendl(ft_strsub(path, 2, ft_strlen(path)));
			return (NULL);
		}
		ft_error(1, path);
		return (NULL);
	}
	elem = ft_readdir_bis(dir, r);
	closedir(dir);
	return (elem);
}

int				ft_is_dir(char *path)
{
	struct stat b;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_is_dir\n");
#endif

	if (lstat(path, &b) == -1)
	{
		if (errno == ENOTDIR)
			return (0);
		return (ft_error(1, path));
	}
	if (S_ISDIR(b.st_mode))
		return (1);
	else if (S_ISLNK(b.st_mode))
		return (2);
	return (0);
}
