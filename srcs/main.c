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
		exit (ft_error(NULL));
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
	printf("%s\n", str);

	if (droit[0] == '-')
		return (0);
	else
		return (1);
}

char **ft_readdir(char *path)
{
	int		i;
	char *tmp;
	struct dirent *dp;
	char **lst;
	DIR *dir;

	if (path == NULL)
		dir = opendir(".");
	else
		dir = opendir(path);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			printf("%s\n", path);
			exit (0);
		}
		exit (ft_error(NULL));
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
	closedir(dir);
	lst = ft_strsplit(tmp, '\n');
	ft_sort_str(&lst, i);
	return (lst);
}

int main(int ac, const char **av)
{
	char **lst;
	char **lst2;
	char *path;
	int pospath;
	char option;
	int i;
ac = 0;

	pospath = 1;
	if (ft_strchr(av[1], '-') != NULL)
	{
		pospath++;
		option = av[1][1];
	}

	lst = ft_readdir((char*)av[pospath]);
	i = 0;
	path = "";
	if (av[pospath][ft_strlen(av[pospath]) - 1] != '/')
		path = ft_strjoin(av[pospath], "/");
	printf("%s\n", path);
	while (lst[i])
	{
		if (printinfo(path, lst[i]) == 1 && lst[i][0] != '.')
		{
			printf("%s%s\n", path, lst[i]);
			lst2 = ft_readdir(ft_strjoin(path, lst[i]));
			printinfo(path, lst[i]);
		}
		i++;
	}

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
