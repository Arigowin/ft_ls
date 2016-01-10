#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
void	ft_free_lst(t_ft_ls data)
{
	int i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_free_lst\n");
#endif

	i = 0;
	while (i < data.nb_path)
	{
		free(data.path[i]);
		i++;
	}
	free(data.path);
}
