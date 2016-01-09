#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/xattr.h>

#include <stdio.h>
int		printinfo(char *path, char *str)
{
	struct stat b;
	struct passwd *uid;
	struct group *grp;
	char *droit;
	char *tmp;

	tmp = NULL;
	if (lstat(ft_strjoin(path, str), &b) == -1)
		exit (ft_error(1, path));
	droit = ft_modeoffile(b.st_mode);
	uid = getpwuid(b.st_uid);
	grp = getgrgid(b.st_gid);

	ft_putstr(droit);
	ft_putstr("\t");
	ft_putnbr(b.st_nlink);
	ft_putstr("\t");
	ft_putstr(uid->pw_name);
	ft_putstr("\t");
	ft_putstr(grp->gr_name);
	ft_putstr("\t");
	if (!(b.st_rdev))
		ft_putnbr(b.st_size);
	else
	{
		ft_putnbr((b.st_rdev & MAJOR) >> 24);
		ft_putstr(", ");
		ft_putnbr(b.st_rdev & ~MAJOR);
	}
	ft_putstr("\t");
	ft_putstr(ft_format_date(b.st_mtime));
	ft_putstr("\t");
	if (str[0] != '\0')
		ft_putendl(str);
	else
		ft_putendl(path);

	if (droit[0] == '-')
		return (0);
	else
		return (1);
}

void	ft_free_lst(t_ft_ls data)
{
	int i;

	i = 0;
	free(data.op);
	while (i < data.nb_path)
	{
		free(data.path[i]);
		i++;
	}
	free(data.path);
}

int main(int ac, char **av)
{
	t_ft_ls		data;

	data.nb_path = 0;
	data.path = NULL;
	data.op = NULL;

	ft_get_arg(&data, av, ac);
	if (data.nb_path > 1)
		ft_sort_str(&(data.path), data.nb_path);
	if (ft_check_op(data.op))
		exit(-1);

	ft_browse(data);

	ft_free_lst(data);

	return (0);
}

/*
// st_dev | MAJOR = hexa FF nb a garder | >> 24 pour deplacer de 24 bit sur la droite cad de 4 * 6 bit
printf("%d\t\t%d\n", major(b.st_rdev), (b.st_rdev & MAJOR) >> 24);
printf("%d\t\t%d\n", minor(b.st_rdev), b.st_rdev & ~MAJOR);
*/

/*
   printf("Nom: %s\n", av[1]);
   droit = ft_modoffile(b.st_mode);
   droit[0] = ft_typeoffile(b.st_mode, &tmp);
   printf("Type: %s\n", tmp);
   printf("Modes: %s\n", droit);
   printf("Nombre de liens: %hu\n", b.st_nlink);
   uid = getpwuid(b.st_uid);
   printf("Proprietaire: %s\n", uid->pw_name);
   grp = getgrgid(b.st_gid);
   printf("Groupe: %s\n", grp->gr_name);
   if (!(b.st_rdev))
   printf("Taille : %lld octets\n", b.st_size);
   else
   printf("Poid de bit majeur, mineur: %d, %d\n", ((b.st_rdev & MAJOR) >> 24), (b.st_rdev & ~MAJOR));
   printf("Date de derniere modification: %s\n", ft_format_date(b.st_mtime));
   */
/*
   char **lst;
   char **lst2;
   char *path;
   char *path2;
   int pospath;
   char option;
   int i;
   int j;
   ac = 0;

   pospath = 1;
   if (ft_strchr(av[1], '-') != NULL)
   {
   pospath++;
   option = av[1][1];
   }
   path = "";
   if (av[pospath][ft_strlen(av[pospath]) - 1] != '/')
   path = ft_strjoin(av[pospath], "/");
   else
   path = ft_strdup(av[pospath]);

   lst = ft_readdir((char*)av[pospath]);
   i = 0;
   printf("%s\n", path);
   while (lst[i])
   {
   if (printinfo(path, lst[i]) == 1 && lst[i][0] != '.' && pospath == 2)
   {
   j = 0;
   printf("\n%s%s\n", path, lst[i]);
   lst2 = ft_readdir(ft_strjoin(path, lst[i]));
   while(lst2[j])
   {
   if (lst2[j][0] != '.')
   {
   path2 = ft_strnew(ft_strlen(path) + ft_strlen(lst[i]) + 1);
   path2 = ft_strcat(path2, path);
   path2 = ft_strcat(path2, lst[i]);
   path2 = ft_strcat(path2, "/");
   printinfo(path2, lst2[j]);
   }
   j++;
   }
   }
   i++;
   }
   */
