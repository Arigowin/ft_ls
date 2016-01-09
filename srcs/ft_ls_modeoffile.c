#include "ft_ls.h"
# include "libft.h"
#include <sys/stat.h>

#include <stdio.h>
static char		ft_typeoffile(mode_t mode)
{
	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_typeoffile\n");
#endif

	char droit;

	droit = '-';
	if (S_ISREG (mode))
		droit = '-';
	else if (S_ISDIR (mode))
		droit = 'd';
	else if (S_ISLNK (mode))
		droit = 'l';
	else if (S_ISFIFO (mode))
		droit = 'p';
	else if (S_ISBLK (mode))
		droit = 'b';
	else if (S_ISCHR (mode))
		droit = 'c';
	else if (S_ISSOCK (mode))
		droit = 's';
	else
		droit = '?';
	return (droit);
}

char			*ft_modeoffile(mode_t mode)
{
	char *droit;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : ft_modeoffile\n");
#endif

	droit = ft_strnew(10);
	droit = ft_memset(droit, '-', 10);
	if (S_IRUSR & mode)
		droit[1] = 'r';
	if (S_IWUSR & mode)
		droit[2] = 'w';
	if (S_IXUSR & mode)
		droit[3] = 'x';
	if (S_IRGRP & mode)
		droit[4] = 'r';
	if (S_IWGRP & mode)
		droit[5] = 'w';
	if (S_IXGRP & mode)
		droit[6] = 'x';
	if (S_IROTH & mode)
		droit[7] = 'r';
	if (S_IWOTH & mode)
		droit[8] = 'w';
	if (S_IXOTH & mode)
		droit[9] = 'x';
	droit[0] = ft_typeoffile(mode);
	return (droit);
}
