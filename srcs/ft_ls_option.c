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
#include <errno.h>

#include <stdio.h>
#include <unistd.h>
void		ft_set_op(char *op, t_ft_ls *data)
{
	int	i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_set_option\n");
#endif

	i = 0;
	ft_check_op(op);
	ft_check_arg(*data);
	while (op[i])
	{
		if (!data->op_recu)
			data->op_recu = (op[i] == 'R' ? 1 : 0);
		if (!data->op_a)
			data->op_a = (op[i] == 'a' ? 1 : 0);
		if (!data->op_l)
			data->op_l = (op[i] == 'l' ? 1 : 0);
		if (!data->op_r)
			data->op_r = (op[i] == 'r' ? 1 : 0);
		if (!data->op_t)
			data->op_t = (op[i] == 't' ? 1 : 0);
		i++;
	}
}

static char		*ft_get_option(char **lst, int *nb)
{
	int		i;
	char	*ret;
	int		nbb;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_get_option\n");
#endif

	i = 1;
	nbb = (*nb);
	ret = ft_strnew(*nb);
	while (i < nbb && lst[i][0] == '-' && lst[i][1] != '\0')
	{
		if (ft_strcmp(lst[i], "--") != 0)
		{
			if (lst[i][0] == '-' && lst[i][1] != '\0')
			{
				ret = ft_strjoin(ret, ft_strdup(&lst[i][1]));
			}
		}
		else
		{
			(*nb)--;
			break ;
		}
		i++;
		(*nb)--;
	}
	(*nb)--;
	return (ret);
}

char			*ft_get_arg(t_ft_ls *data, char **lst, int nb)
{
	int		i;
	int		j;
	int		nbb;
	char	*op;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_get_arg\n");
#endif

	nbb = nb;
	op = ft_get_option(lst, &nb);
	if ((data->path = (char **)malloc(sizeof(char *) * (((nb) == 0 ? 1 : nb) + 1))) == NULL)
		ft_error(1, "ft_get_arg");
	if (nb < 1)
	{
		data->path[0] = NULL;
		data->path[0] = ft_strdup(".");
		data->path[1] = NULL;
		data->nb_path++;
		return (op);
	}
	i = nbb - nb;
	j = 0;
	while (i < nbb)
	{
		data->path[j] = NULL;
		data->path[j] = ft_strdup(lst[i]);
		j++;
		i++;
		data->nb_path++;
	}
	data->path[j] = NULL;
	return (op);
}

int				ft_check_op(char *op)
{
	char	*lstop;
	int		i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_check_op\n");
#endif

	lstop = OP;
	i = 0;
	while (op[i])
	{
		if (ft_strchr(lstop, op[i]) == NULL)
			exit (ft_error(2, &(op[i])));
		i++;
	}
	return (0);
}

int			ft_check_arg(t_ft_ls data)
{
#ifdef DEBUG
	printf("DEBUG : ft_check_arg\n");
#endif
	int i;

	i = 0;
	while (i < data.nb_path)
	{
		if (data.path[i][0] == '\0')
		{
			errno = ENOENT;
			exit(ft_error(1, "fts_open"));
		}
		i++;
	}
	return (0);
}
