/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_browse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:02 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 18:22:49 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static int		ft_browse_not_a_dir_bis(t_ft_ls **data, t_elem **elem, int i)
{
	t_elem	*new;

	new = ft_elem_new((*data)->path[i]);
	if ((*data)->op_l || (*data)->op_t)
		(*data)->total += ft_get_info("./", new, (*data));
	ft_elem_insert(elem, new, (*data)->op_r, (*data)->op_t);
	ft_strdel(&((*data)->path[i]));
	return (1);
}

static int		ft_browse_not_a_directorie(t_ft_ls *data, t_elem *elem)
{
	int		i;
	int		j;
	int		er;

	i = 0;
	j = 0;
	while (i < data->nb_path)
	{
		if (((er = ft_is_dir(data->path[i])) == 0 && er != -1) || (er == 2))
		{
			j += ft_browse_not_a_dir_bis(&data, &elem, i);
		}
		if (er == -1)
			ft_strdel(&(data->path[i]));
		i++;
	}
	if (elem && j != 0)
		ft_print(data, &elem, 0, j);
	if (elem != NULL)
		ft_free_elem(&elem, data->op_l, data->op_t);
	return (j);
}

void			ft_browse(t_ft_ls *data)
{
	t_elem	*elem;
	char	*tmp;
	int		i;
	int		j;

	elem = NULL;
	j = ft_browse_not_a_directorie(data, elem);
	i = 0;
	while (i < data->nb_path)
	{
		if (data->path[i] != NULL)
		{
			tmp = ft_strdup(data->path[i]);
			ft_browse_recu(data, tmp, i + j);
		}
		i++;
	}
}
