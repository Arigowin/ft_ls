#include "ft_ls.h"

int		ft_error(char *str)
{
	if (str != NULL)
	{
		ft_putstr("ft_ls: ");
		perror(str);
	}
	else
	{
		ft_putstr("ft_ls: ");
		perror(str);
	}
	return (-1);
}
