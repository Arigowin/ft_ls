/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:23 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 18:28:11 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void		ft_printone(t_elem *elem, size_t *size, int rdev, int op_l)
{
	if (op_l)
	{
		ft_printone1(elem, size);
		ft_printone2(elem, size, rdev);
		ft_printone3(elem);
		ft_putendl("");
	}
	else
		ft_putendl(elem->name);
}

static void		ft_print_while(t_elem **elem, t_ft_ls data, int t)
{
	t_elem	*tmp;

	tmp = *elem;
	while (tmp)
	{
		if ((data.op_a || tmp->name[0] != '.' || !t) && tmp->name != NULL)
		{
			if (data.size[4] == 0)
				ft_printone(tmp, data.size, 0, data.op_l);
			else
				ft_printone(tmp, data.size, 1, data.op_l);
		}
		tmp = tmp->next;
	}
}

void			ft_print(t_ft_ls *data, t_elem **elem, char t, int nb)
{
	if (data->op_l && t && (nb > 2 || data->op_a))
	{
		ft_putstr("total ");
		ft_putnbrendl(data->total);
		data->total = 0;
	}
	ft_print_while(elem, *data, t);
	data->size[0] = 0;
	data->size[1] = 0;
	data->size[2] = 0;
	data->size[3] = 0;
	data->size[4] = 0;
}
