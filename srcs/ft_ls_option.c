/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:21 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 17:05:07 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

void			ft_set_op(char *op, t_ft_ls *data)
{
	int	i;

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
	char	*ret;
	char	*tmp;
	int		i;
	int		nbb;

	i = 1;
	nbb = (*nb);
	ret = ft_strnew(*nb);
	while (i < nbb && lst[i][0] == '-' && lst[i][1] != '\0')
	{
		if (ft_strcmp(lst[i], "--") != 0)
		{
			if (lst[i][0] == '-' && lst[i][1] != '\0')
			{
				tmp = ft_strdup(&lst[i][1]);
				ft_strproperjoin(&ret, &tmp);
				free(tmp);
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
	char	*op;
	int		i;
	int		j;
	int		nbb;

	nbb = nb;
	op = ft_get_option(lst, &nb);
	if ((data->path = (char **)malloc(sizeof(char *) *
					(((nb) == 0 ? 1 : nb) + 1))) == NULL)
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

	lstop = OP;
	i = 0;
	while (op[i])
	{
		if (ft_strchr(lstop, op[i]) == NULL)
			exit(ft_error(2, &(op[i])));
		i++;
	}
	return (0);
}

int				ft_check_arg(t_ft_ls data)
{
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
