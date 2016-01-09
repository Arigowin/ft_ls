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

static char		*ft_get_option(char **lst, int *nb)
{
	int		i;
	char	*ret;
	int		nbb;

	i = 1;
	nbb = (*nb);
	ret = ft_strnew(*nb);
	while (i < nbb && lst[i][0] == '-' && lst[i][1] != '\0')
	{
		if (lst[i][1] != '-')
		{
			if (lst[i][0] == '-' && lst[i][1] != '\0')
				ret = ft_strjoin(ret, &lst[i][1]);
			i++;
			(*nb)--;
		}
		else
		{
			(*nb)--;
			break ;
		}
	}
	(*nb)--;
	return (ret);
}

void			ft_get_arg(t_ft_ls *data, char **lst, int nb)
{
	int		i;
	int		j;
	int		nbb;

	nbb = nb;
	data->op = ft_get_option(lst, &nb);
	if ((data->path = (char **)malloc(sizeof(char *) * (((nbb - nb) <= 0 ? 1 : nbb - nb) + 1))) == NULL)
		ft_error(1, "ft_get_arg");
	if (nb < 1)
	{
		data->path[0] = ft_strdup(".");
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

int				ft_check_op(char *op)
{
	char	*lstop;
	int		i;

	lstop = OP;
	i = 0;
	while (op[i])
	{
		if (ft_strchr(lstop, op[i]) == NULL)
			return (ft_error(2, &(op[i])));
		i++;
	}
	return (0);
}
