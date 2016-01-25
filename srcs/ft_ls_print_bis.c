/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 18:15:03 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 18:31:38 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void			ft_printone1(t_elem *elem, size_t *size)
{
	size_t		i;

	ft_putstr(elem->droit);
	ft_putstr("  ");
	i = -1;
	while (++i < size[0] - ft_strlen(elem->nlink))
		ft_putchar(' ');
	ft_putstr(elem->nlink);
	ft_putstr(" ");
	ft_putstr(elem->uid);
	i = -1;
	while (++i < size[1] - ft_strlen(elem->uid))
		ft_putchar(' ');
	ft_putstr("  ");
	ft_putstr(elem->grp);
	i = -1;
	while (++i < size[2] - ft_strlen(elem->grp))
		ft_putchar(' ');
	ft_putstr("  ");
}

void			ft_printone2(t_elem *elem, size_t *size, int rdev)
{
	size_t		i;
	size_t		t;

	if (elem->size != NULL)
	{
		i = -1;
		t = (rdev ? size[4] + size[3] + 2 : size[3] - ft_strlen(elem->size));
		while (++i < t)
			ft_putchar(' ');
		ft_putstr(elem->size);
	}
	else
	{
		ft_putstr(" ");
		i = -1;
		while (++i < size[3] - ft_strlen(elem->rdevmineur))
			ft_putchar(' ');
		ft_putstr(elem->rdevmineur);
		ft_putstr(", ");
		i = -1;
		while (++i < (size[4] - ft_strlen(elem->rdevmajeur)))
			ft_putchar(' ');
		ft_putstr(elem->rdevmajeur);
	}
}

void			ft_printone3(t_elem *elem)
{
	ft_putstr(" ");
	ft_putstr(elem->date);
	ft_putstr(" ");
	if (elem->droit[0] == 'l')
		ft_putstr_color(PURPLE, elem->name);
	else if (elem->droit[0] == 'd')
		ft_putstr_color(CYAN, elem->name);
	else if (ft_strchr(elem->droit, 'x') != NULL)
		ft_putstr_color(GREEN, elem->name);
	else
		ft_putstr(elem->name);
	if (elem->link != NULL)
	{
		ft_putstr(" -> ");
		ft_putstr(elem->link);
	}
}
