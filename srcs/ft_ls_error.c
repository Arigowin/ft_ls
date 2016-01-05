#include "ft_ls.h"

int		ft_error(char *str)
{
	if (str != NULL)
	{
		ft_putstr("ERROR : ");
		ft_putstr(str);
		ft_putstr(" : ");
		ft_putendl(strerror(errno));
	}
	else
	{
		ft_putstr("ERROR : ");
		ft_putendl(strerror(errno));
	}
	return (-1);
}
