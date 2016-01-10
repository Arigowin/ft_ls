#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/xattr.h>
#include <stdlib.h>

#include <stdio.h>
void	print(t_elem **elem, char *path)
{
	struct stat st;
	int			i;

	i = 0;
	while(i < (*elem)[i].nbelem)
	{
		if (lstat(ft_strjoin(path, (*elem)[i].name), &st) == -1)
			exit (ft_error(1, (*elem)[i].name));
		(*elem)[i].droit = ft_modeoffile(st.st_mode);
		(*elem)[i].nlink = ft_itoa(st.st_nlink);
		(*elem)[i].uid = (getpwuid(st.st_uid))->pw_name;
		(*elem)[i].grp = (getgrgid(st.st_gid))->gr_name;
		// save la taille la plus grande
		(*elem)[i].size = ft_itoa(st.st_size);
		(*elem)[i].date = ft_format_date(st.st_mtime);

		i++;
	}
	// boucler pour afficher les info
}

int		printinfo(char *path, char *str)
{
	struct stat b;
	struct passwd *uid;
	struct group *grp;
	char *droit;
	char *tmp;
/*
	char *taillelaplusgrandelink;
	char *taillelaplusgrandesize;*/
	char *nlink;
	char *size;
	
	// DEBUG
#ifdef DEBUG
	printf("DEBUG : printinfo\n");
#endif

	tmp = NULL;
	if (lstat(ft_strjoin(path, str), &b) == -1)
		exit (ft_error(1, path));
	droit = ft_modeoffile(b.st_mode);
	uid = getpwuid(b.st_uid);
	grp = getgrgid(b.st_gid);

	ft_putstr(droit);
	ft_putstr("  ");
	nlink = ft_itoa(b.st_nlink);
	////////////////
	if (ft_strlen(nlink) < 2)
			ft_putstr(" ");
	////////////////
	ft_putstr(nlink);
	ft_putstr(" ");
	ft_putstr(uid->pw_name);
	ft_putstr(" ");
	ft_putstr(grp->gr_name);
	ft_putstr(" ");
	if (!(b.st_rdev))
	{
		size = ft_itoa(b.st_size);
		ft_putstr(size);
	}
	else
	{
		ft_putnbr((b.st_rdev & MAJOR) >> 24);
		ft_putstr(", ");
		ft_putnbr(b.st_rdev & ~MAJOR);
	}
	ft_putstr(" ");
	ft_putstr(ft_format_date(b.st_mtime));
	ft_putstr(" ");
	if (str[0] != '\0')
		ft_putendl(str);
	else
		ft_putendl(path);

	if (droit[0] == '-')
		return (0);
	else
		return (1);
}

int main(int ac, char **av)
{
	t_ft_ls		data;
	char		*op;

	data.nb_path = 0;
	data.path = NULL;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : main\n");
#endif

	op = ft_get_arg(&data, av, ac);
	ft_set_op(op, &data);
	if (data.nb_path > 1)
		ft_sort_str(&(data.path), data.nb_path);

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
