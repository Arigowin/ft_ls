// option a gerer : 
// -l : list one file per line.
// -R : list subdirectories recursively
// -a : do not ignore entries starting with .
// -r : reverse order while sorting
// -t : sort by modification time, newest first

#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>

int		ft_is_dir(char *path, char *fpath)
{
	struct stat b;
	if (lstat(fpath, &b) == -1)
		exit(ft_error(path));
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
			exit(ft_error("4"));
	}
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	if (ft_is_dir(str, path) == 0)
		return (str);
	return (path);
}
static char		*ft_recup_option(char **lst, int *nb)
{
	int		i;
	char	*ret;
	int		nbb;

	i = 1;
	nbb = (*nb);
	ret = ft_strnew(*nb);
	while (i < nbb && lst[i][0] == '-' && lst[i][1] != '\0')
	{
		if (lst[i][0] == '-' && lst[i][1] != '\0')
			ret = ft_strjoin(ret, &lst[i][1]);
		i++;
		(*nb)--;
	}
	(*nb)--;
	return (ret);
}

void			ft_recup_arg(t_ft_ls *data, char **lst, int nb)
{
	int		i;
	int		j;
	int		nbb;

	data->path = (char **)malloc(sizeof(char *) * nb);
	data->path_format = (char **)malloc(sizeof(char *) * nb);
	nbb = nb;
	data->op = ft_recup_option(lst, &nb);
	if (nb < 1)
	{
		data->path[0] = ".";
		data->path[1] = NULL;
		data->nb_path++;
		return ;
	}
	i = nbb - nb;
	j = 0;
	while (i < nbb)
	{
		data->path[j++] = ft_strdup(lst[i++]);
		data->nb_path++;
	}
	data->path[data->nb_path] = NULL;
}
