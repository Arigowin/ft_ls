#include "ft_ls.h"

int		ft_error(char *str)
{
	if (str != NULL)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(str);
		ft_putstr(": ");
		ft_putendl(strerror(errno));
	}
	else
	{
		ft_putstr("ft_ls: ");
		ft_putendl(strerror(errno));
	}
	return (-1);
}
