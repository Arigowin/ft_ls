// option a gerer : 
// -l : list one file per line.
// -R : list subdirectories recursively
// -a : do not ignore entries starting with .
// -r : reverse order while sorting
// -t : sort by modification time, newest first

#include "ft_ls.h"

int		ft_is_dir(char *path, char *fpath)
{
	struct stat b;

	if (lstat(path, &b) == -1)
		exit(ft_error(fpath));
	if (S_ISDIR (b.st_mode))
		return (1);
	else
		return (0);
}

char			*ft_format_path(char *str)
{
	char	*path;

	path = ft_strdup(str);
	if (str[0] != '/' && str[1] != '/')
	{
		if ((str = ft_strjoin("./", str)) == NULL)
			exit(ft_error(NULL));
	}
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	if (ft_is_dir(str, path) == 0)
		return (str);
	return (path);
}

void			ft_recup_option(t_ft_ls *data, char **lst, int nb)
{
	int i;
	int j;

	data->op = ft_strnew(nb);
	data->path = (char **)malloc(sizeof(char *) * nb);
	data->path_format = (char **)malloc(sizeof(char *) * nb);
	i = 1;
	j = 1;
	if (nb < 2 || (nb < 3 && lst[1][0] == '-'))
	{
		data->path[0] = ".";
		data->nb_path++;
		return ;
	}
	if (lst[1][0] == '-' && lst[1][1] != '\0')
	{
		i = 2;
		while (lst[1][j])
		{
			data->op[j - 1] = lst[1][j];
			j++;
		}
	}
	j = 0;
	while (i < nb)
	{
		data->path[j++] = ft_strdup(lst[i++]);
		data->nb_path++;
	}
	data->path[j] = NULL;
}
