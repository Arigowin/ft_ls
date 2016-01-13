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
		{
			free(data->path[i]);
		}
		i++;
	}
	free(data->path);
}

void	ft_free_elem(t_elem **elem)
{
	int		i;

	i = 0;
	while (i < (*elem)[0].nbelem)
	{
		free((*elem)[i].name);
		if ((*elem)[i].droit != NULL)
			free((*elem)[i].droit);
		if ((*elem)[i].nlink != NULL)
			free((*elem)[i].nlink);
		if ((*elem)[i].uid != NULL)
			free((*elem)[i].uid);
		if ((*elem)[i].grp != NULL)
			free((*elem)[i].grp);
		if ((*elem)[i].size != NULL)
			free((*elem)[i].size);
		if ((*elem)[i].date != NULL)
			free((*elem)[i].date);
		if ((*elem)[i].sec_date != NULL)
			free((*elem)[i].sec_date);
		if ((*elem)[i].rdevmajeur != NULL)
			free((*elem)[i].rdevmajeur);
		if ((*elem)[i].rdevmineur != NULL)
			free((*elem)[i].rdevmineur);
		if ((*elem)[i].link != NULL)
			free((*elem)[i].link);
		i++;
	}
}
