#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
void	ft_free_lst(t_ft_ls *data)
{
	int i;

	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : ft_free_lst\n");
#endif

	i = 0;
	while (i < data->nb_path)
	{
		if (data->path[i] != NULL)
			free(data->path[i]);
		i++;
	}
	free(data->path);
}

void	ft_free_elem(t_elem **elem, char l, char t)
{
	// DEBUG
#ifdef DEBUG
	ft_putstr("DEBUG : ft_free_elem\n");
#endif
	t_elem	*tmp;

	while (*elem)
	{
		free((*elem)->name);
		if (l)
		{
			free((*elem)->droit);
			free((*elem)->nlink);
			free((*elem)->uid);
			free((*elem)->grp);
			free((*elem)->size);
			free((*elem)->rdevmajeur);
			free((*elem)->rdevmineur);
			free((*elem)->link);
		}
		if (l || t)
			free((*elem)->date);
		tmp = (*elem)->next;
		free(*elem);
		*elem = tmp;
	}
}
