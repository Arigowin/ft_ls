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
	char			*tmp3;
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
	tmp2 = NULL;
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
			tmp3 = ft_strjoin(tmp, "\n");
			ft_strdel(&tmp);
			tmp = ft_strjoin(tmp3, dp->d_name);
			ft_strdel(&tmp3);
			tmp3 = ft_strjoin(tmp2, ":");
			ft_strdel(&tmp2);
			tmpc = ((char)dp->d_type != 0 ? (char)dp->d_type : 42);
			tmp2 = ft_strjoin(tmp3, &tmpc);
			ft_strdel(&tmp3);
		}
		i++;
	}
	if (dp == NULL && (tmp == NULL || tmp2 == NULL))
		ft_error(1, "ft_read_bis");
	lst = ft_strsplit(tmp, '\n');
	lst2 = ft_strsplit(tmp2, ':');
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	if ((elem = (t_elem *)malloc(sizeof(t_elem) * i)) == NULL)
		exit (ft_error(1, "ft_readdir_bis"));
	j = 0;
	while (lst[j])
	{
		ft_init_t_elem(&(elem[j]));
		elem[j].name = ft_strdup(lst[j]);
		elem[j].type = lst2[j][0];
		elem[j].nbelem = i;
		j++;
	}
	ft_free_tbl_s(lst);
	ft_free_tbl_s(lst2);
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

	if ((dir = opendir(fpath)) == NULL)
	{
		ft_error(1, path);
		return (NULL);
	}
	elem = ft_readdir_bis(dir);
	closedir(dir);
	return (elem);
}

int		ft_is_dir(char *path)
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
	return (S_ISDIR (b.st_mode));
}
