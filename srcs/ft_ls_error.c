#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	return (EXIT_FAILURE);
}
