#include "ft_ls.h"
#include "libft.h"

#include <stdio.h>
int main(int ac, char **av)
{
	t_ft_ls		data;
	char		*op;

	ft_init_t_ft_ls(&data);

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : main\n");
#endif

	op = ft_get_arg(&data, av, ac);
	ft_set_op(op, &data);
	if (data.nb_path > 1)
		ft_sort_str(&(data.path), data.nb_path);

	ft_browse(data);

	//ft_free_lst(data);

	return (0);
}
