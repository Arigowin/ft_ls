/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:08 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 16:50:18 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		ft_error(int nb, char *str)
{
	if (nb == 1)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(str);
	}
	else if (nb == 2)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putstr_fd("\nusage: ft_ls [-", 2);
		ft_putstr_fd(OP, 2);
		ft_putendl_fd("] [file ...]", 2);
	}
	return (-1);
}
