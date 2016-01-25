/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:48:05 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 18:12:20 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

t_elem		*ft_elem_new(char *name)
{
	t_elem	*new;

	if ((new = (t_elem *)malloc(sizeof(t_elem))) == NULL)
		exit(ft_error(1, "ft_elem_new"));
	ft_init_t_elem(new);
	if ((new->name = ft_strdup(name)) == NULL)
		exit(ft_error(1, name));
	return (new);
}

static void	ft_elem_insert_bis(t_elem **aelem, t_elem *new, char r)
{
	t_elem	*tmp;
	int		cmp;

	tmp = *aelem;
	if ((cmp = (r ? ft_strcmp(tmp->name, new->name) :
					ft_strcmp(new->name, tmp->name)) < 0))
	{
		new->next = tmp;
		*aelem = new;
	}
	else if (tmp->next == NULL)
		tmp->next = new;
	else
	{
		while (tmp->next != NULL
				&& (cmp = (r ? ft_strcmp(tmp->next->name, new->name) :
						ft_strcmp(new->name, tmp->next->name)) > 0))
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

static void	ft_elem_insert_bis_t(t_elem **aelem, t_elem *new, char r)
{
	t_elem	*tmp;
	int		cmp;

	tmp = *aelem;
	if ((cmp = (r ? (new->sec_date - tmp->sec_date) +
		(ft_strcmp(tmp->name, new->name)) : (tmp->sec_date - new->sec_date) +
		(ft_strcmp(new->name, tmp->name)))) < 0)
	{
		new->next = tmp;
		*aelem = new;
	}
	else if (tmp->next == NULL)
		tmp->next = new;
	else
	{
		while (tmp->next != NULL && (cmp = (r ?
				(new->sec_date - tmp->next->sec_date) +
				(ft_strcmp(tmp->next->name, new->name)) :
				(tmp->next->sec_date - new->sec_date) +
				(ft_strcmp(new->name, tmp->next->name)))) > 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void		ft_elem_insert(t_elem **aelem, t_elem *new, char r, char t)
{
	if (*aelem == NULL)
		*aelem = new;
	else
	{
		if (!t)
			ft_elem_insert_bis(aelem, new, r);
		else
			ft_elem_insert_bis_t(aelem, new, r);
	}
}
