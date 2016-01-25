/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:29 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 17:07:32 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_ft_ls		data;
	char		*op;

	ft_init_t_ft_ls(&data);
	op = ft_get_arg(&data, av, ac);
	ft_set_op(op, &data);
	if (data.nb_path > 1)
		ft_sort_str(&(data.path), data.nb_path, data.op_r);
	ft_browse(&data);
	ft_free_lst(&data);
	ft_strdel(&op);
	return (0);
}
