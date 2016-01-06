#include "ft_ls.h"


int		printinfo(char *path, char *str)
{
	struct stat b;
	struct passwd *uid;
	struct group *grp;
	char *droit;
	char *tmp;

	tmp = NULL;
	if (lstat(ft_strjoin(path, str), &b) == -1)
		exit (ft_error(ft_strjoin(path, str)));
	droit = ft_modeoffile(b.st_mode);
	printf("%s\t", droit);
	printf("%hu\t", b.st_nlink);
	uid = getpwuid(b.st_uid);
	printf("%s\t", uid->pw_name);
	grp = getgrgid(b.st_gid);
	printf("%s\t", grp->gr_name);
	if (!(b.st_rdev))
		printf("%lld\t", b.st_size);
	else
		printf("%d, %d\t", ((b.st_rdev & MAJOR) >> 24), (b.st_rdev & ~MAJOR));
	printf("%s\t", ft_format_date(b.st_mtime));
	if (str[0] != '\0')
		printf("%s\n", str);
	else
		printf("%s\n", ft_strsub(path, 2, ft_strlen(path) - 2));

	if (droit[0] == '-')
		return (0);
	else
		return (1);
}

// fonction qui me renvoie 0 si ces un fichier et 1 si ces un dossier

int main(int ac, const char **av)
{
	t_ft_ls		data;
	char		**lst;
	int i = 0;
	int j = 0;

	data.nb_path = 0;
	data.path = NULL;
	data.op = NULL;
	ft_recup_option(&data, (char**)av, ac);
	if (data.nb_path < 1)
		ft_sort_str(&(data.path), data.nb_path);

	printf("option: [%s]\n", data.op);
	while (data.path[i] != NULL)
	{
		j = 0;
		data.path_format[i] = ft_format_path(data.path[i]);
		printf("\n%s:\n", data.path[i]);
		if (ft_is_dir(data.path[i], data.path_format[i]) == 1)
		{
			if ((lst = ft_readdir(data.path_format[i], data.path[i])) == NULL)
			{
				i++;
				continue ;
			}
			while (lst[j] != NULL)
			{
				printinfo(data.path_format[i], lst[j]);
				j++;
			}
		}
		else
		{
			printinfo(data.path_format[i], "");
		}
		i++;
	}


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
