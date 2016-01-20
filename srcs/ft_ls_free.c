#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
void	ft_free_lst(t_ft_ls *data)
{
	int i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_free_lst\n");
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

void	ft_free_elem(t_elem **elem)
{
	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_free_elem\n");
#endif
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = *elem;
	while (tmp)
	{
	//	free(tmp->name);
	//	free(tmp->droit);
	//	free(tmp->nlink);
	//	free(tmp->uid);
	//	free(tmp->grp);
	//	free(tmp->size);
	//	free(tmp->date);
	//	free(tmp->rdevmajeur);
	//	free(tmp->rdevmineur);
	//	free(tmp->link);
		tmp2 = tmp->next;
	//	free (tmp);
		tmp = tmp2;
	}
	//free (elem);
}
