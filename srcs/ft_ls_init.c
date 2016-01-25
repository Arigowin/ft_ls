/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:17 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 17:03:35 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

void	ft_init_t_ft_ls(t_ft_ls *data)
{
	data->path = NULL;
	data->op_recu = 0;
	data->op_a = 0;
	data->op_l = 0;
	data->op_r = 0;
	data->op_t = 0;
	data->nb_path = 0;
	data->total = 0;
	data->size[0] = 0;
	data->size[1] = 0;
	data->size[2] = 0;
	data->size[3] = 0;
	data->size[4] = 0;
}

void	ft_init_t_elem(t_elem *elem)
{
	elem->name = NULL;
	elem->droit = NULL;
	elem->nlink = NULL;
	elem->uid = NULL;
	elem->grp = NULL;
	elem->size = NULL;
	elem->date = NULL;
	elem->rdevmineur = NULL;
	elem->rdevmajeur = NULL;
	elem->link = NULL;
	elem->next = NULL;
	elem->type = 0;
	elem->sec_date = 0;
}
