#include "ft_ls.h"



int main(int ac, const char **av)
{
	struct stat b;
	struct passwd *uid;
	struct group *grp;
	char *tmp;
	char *droit;
	char **lst;
	int		i;

	DIR *dir;
	struct dirent *dp;

	if (ac == 1)
		dir = opendir(".");
	else
		dir = opendir(av[1]);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			printf("%s\n", av[1]);
			return (0);
		}
		return (ft_error(NULL));
	}
	tmp = NULL;
	i = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (tmp == NULL)
			tmp = ft_strdup(dp->d_name);
		else
		{
			tmp = ft_strjoin(tmp, "\n");
			tmp = ft_strjoin(tmp, dp->d_name);
		}
		i++;
	}
	lst = ft_strsplit(tmp, '\n');
	ft_sort_str(&lst, i);
	i = 0;
	while (lst[i])
	{
		if (lst[i][0] != '.')
		{
			tmp = NULL;
			if (lstat(lst[i], &b) == -1)
				return (ft_error(lst[i]));

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
			printf("%s\n", lst[i]);
		}
		i++;
	}
	closedir(dir);

	return (0);
}
/*
// Recupere la liste des fichiers et dossier dans un dossier donne
DIR *dir;
struct dirent *dp;

dir = opendir(av[1]);
if (dir == NULL)
return (-1);
while ((dp = readdir(dir)) != NULL)
{
printf("%s\n", dp->d_name);
}
closedir(dir);
*/

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
