// option a gerer : 
// -l : list one file per line.
// -R : list subdirectories recursively
// -a : do not ignore entries starting with .
// -r : reverse order while sorting
// -t : sort by modification time, newest first

#include "ft_ls.h"

char			*ft_format_path(char *str)
{
	char	*path;

	if (str[ft_strlen(str) - 1] != '/')
		str = ft_strjoin(str, "/");
	if (str[0] != '/' || (str[0] != '.' && str[0] != '/'))
	{
		path = "./";
		if ((path = ft_strjoin(path, str)) == NULL)
			exit(ft_error(NULL));
	}
	else
	{
		if ((path = ft_strdup(str)) == NULL)
			exit(ft_error(NULL));
	}
	return (path);
}

void			ft_recup_option(t_ft_ls *data, char **lst, int nb)
{
	int i;
	int j;
	int k;
	int l;

	data->op = ft_strnew(nb);
	data->path = (char **)malloc(sizeof(char *) * nb);
	data->path_format = (char **)malloc(sizeof(char *) * nb);
	i = 0;
	j = 0;
	k = 1;
	while (k < nb)
	{
		if (lst[k][0] == '-' && lst[k][1] != '\0')
		{
			data->op[i] = lst[k][1];
			l = 2;
			while (lst[k][l] != '\0')
				data->op[++i] = lst[k][l++];
			i++;
		}
		else
		{
			data->path[j++] = ft_strdup(lst[k]);
			data->nb_path++;
		}
		k++;
	}
	data->path[j] = NULL;
}
