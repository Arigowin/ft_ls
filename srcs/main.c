#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
int	main(int ac, char **av)
{
	t_ft_ls		data;
	char		*op;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : START\nDEBUG : main\n");
#endif

	ft_init_t_ft_ls(&data);
	op = ft_get_arg(&data, av, ac);
	ft_set_op(op, &data);
	if (data.nb_path > 1)
		ft_sort_str(&(data.path), data.nb_path, data.op_r);
	ft_browse(&data);
	ft_free_lst(&data);
	ft_strdel(&op);

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : END\n");
#endif
	return (0);
}
