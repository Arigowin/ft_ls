/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 18:04:59 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 18:05:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

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
