// Commencer par -l -R

#include "ft_ls.h"

char	*ft_modoffile(mode_t mode)
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
	return (droit);
}

char	ft_typeoffile(mode_t mode, char **tmp)
{
	char droit;

	droit = '-';
	//if (S_IFREG & mode)
	if (S_ISREG (mode))
	{
		*tmp = "Fichier";
		droit = '-';
	}
	//else if (S_IFDIR & mode)
	else if (S_ISDIR (mode))
	{
		*tmp = "Repertoire";
		droit = 'd';
	}
	//else if (S_IFLNK & mode)
	else if (S_ISLNK (mode))
	{
		*tmp = "lien symbolique";
		droit = 'l';
	}
	//else if (S_IFIFO & mode)
	else if (S_ISFIFO (mode))
	{
		*tmp = "fifo";
		droit = 'p';
	}
	//else if (S_IFBLK & mode)
	else if (S_ISBLK (mode))
	{
		*tmp = "peripherique bloc";
		droit = 'b';
	}
	//else if (S_IFCHR & mode)
	else if (S_ISCHR (mode))
	{
		*tmp = "peripherique caractere";
		droit = 'c';
	}
	//else if (S_IFSOCK & mode)
	else if (S_ISSOCK (mode))
	{
		*tmp = "socket";
		droit = 's';
	}
	else
	{
		*tmp = "?";
		droit = '?';
	}
	return (droit);
}

char *ft_format_date(time_t date)
{
	char **d;
	char **h;
	char *ret;
	char *tmp;

	tmp = ctime(&(date));
	ret = ft_strnew(ft_strlen(tmp));
	d = ft_strsplit(tmp, ' ');
	h = ft_strsplit(d[3], ':');

	ret = ft_strcat(ret, d[1]);
	ret = ft_strcat(ret, " ");
	ret = ft_strcat(ret, d[2]);
	ret = ft_strcat(ret, " ");
	ret = ft_strcat(ret, h[0]);
	ret = ft_strcat(ret, ":");
	ret = ft_strcat(ret, h[1]);
	return (ret);
}

int main(int ac, const char **av)
{
	struct stat b;
	struct passwd *uid;
	struct group *grp;
	char *tmp;
	char *droit;

	DIR *dir;
	struct dirent *dp;

	dir = opendir(av[1]);
	if (dir == NULL)
		return (-1);
	while ((dp = readdir(dir)) != NULL)
	{
		tmp = NULL;
		if (lstat(dp->d_name, &b) == -1)
		{
			printf("error\n");
			return (-1);
		}

		droit = ft_modoffile(b.st_mode);
		droit[0] = ft_typeoffile(b.st_mode, &tmp);
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
		printf("%s\n", dp->d_name);
	}
	closedir(dir);

	ac = 0;
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
