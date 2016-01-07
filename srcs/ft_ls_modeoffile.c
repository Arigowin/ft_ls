#include "ft_ls.h"
# include "libft.h"
# include <sys/stat.h>

static char		ft_typeoffile(mode_t mode)
{
	char droit;

	droit = '-';
	//if (S_IFREG & mode)
	if (S_ISREG (mode))
		droit = '-';
	//else if (S_IFDIR & mode)
	else if (S_ISDIR (mode))
		droit = 'd';
	//else if (S_IFLNK & mode)
	else if (S_ISLNK (mode))
		droit = 'l';
	//else if (S_IFIFO & mode)
	else if (S_ISFIFO (mode))
		droit = 'p';
	//else if (S_IFBLK & mode)
	else if (S_ISBLK (mode))
		droit = 'b';
	//else if (S_IFCHR & mode)
	else if (S_ISCHR (mode))
		droit = 'c';
	//else if (S_IFSOCK & mode)
	else if (S_ISSOCK (mode))
		droit = 's';
	else
		droit = '?';
	return (droit);
}

char			*ft_modeoffile(mode_t mode)
{
	char *droit;

	droit = ft_strnew(10);
	droit = ft_memset(droit, '-', 10);

	//USER
	if (S_IRUSR & mode)
		droit[0] = 'r';
	if (S_IWUSR & mode)
		droit[1] = 'w';
	if (S_IXUSR & mode)
		droit[2] = 'x';
	//GROUP
	if (S_IRGRP & mode)
		droit[3] = 'r';
	if (S_IWGRP & mode)
		droit[4] = 'w';
	if (S_IXGRP & mode)
		droit[5] = 'x';
	// OTHER
	if (S_IROTH & mode)
		droit[6] = 'r';
	if (S_IWOTH & mode)
		droit[7] = 'w';
	if (S_IXOTH & mode)
		droit[8] = 'x';
	droit[0] = ft_typeoffile(mode);
	return (droit);
}
