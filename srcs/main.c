// Commencer par -l -R

#include "ft_ls.h"

int main(int ac, const char **av)
{
	struct stat *b;
	struct passwd *uid;
	struct group *grp;
	char *tmp;
	char *droit;
	int a;

	tmp = NULL;
	a = 0;
	droit = ft_strnew(10);
	droit = ft_memset(droit, '-', 10);
	b = (struct stat *)malloc(sizeof(struct stat));
	if (stat(av[1], b) == -1)
	{
		printf("error\n");
		return (-1);
	}

	printf("Nom: %s\n", av[1]);

	if (S_IFIFO & b->st_mode)
	{
		tmp = "fifo";
		droit[0] = 'p';
	}
	else if (S_IFCHR & b->st_mode)
	{
		tmp = "peripherique caractere";
		droit[0] = 'c';
	}
	else if (S_IFDIR & b->st_mode)
	{
		tmp = "Repertoire";
		droit[0] = 'd';
	}
	else if (S_IFBLK & b->st_mode)
	{
		tmp = "peripherique bloc";
		droit[0] = 'b';
	}
	else if (S_IFREG & b->st_mode)
	{
		tmp = "Fichier";
		droit[0] = '-';
	}
	else if (S_IFLNK & b->st_mode)
	{
		tmp = "lien symbolique";
		droit[0] = 'l';
	}
	else if (S_IFSOCK & b->st_mode)
	{
		tmp = "socket";
		droit[0] = 's';
	}
	printf("Type: %s\n", tmp);

	//USER
	if (S_IRUSR & b->st_mode)
		droit[1] = 'r';
	if (S_IWUSR & b->st_mode)
		droit[2] = 'w';
	if (S_IXUSR & b->st_mode)
		droit[3] = 'x';
	//GROUP
	if (S_IRGRP & b->st_mode)
		droit[4] = 'r';
	if (S_IWGRP & b->st_mode)
		droit[5] = 'w';
	if (S_IXGRP & b->st_mode)
		droit[6] = 'x';
	// OTHER
	if (S_IROTH & b->st_mode)
		droit[7] = 'r';
	if (S_IWOTH & b->st_mode)
		droit[8] = 'w';
	if (S_IXOTH & b->st_mode)
		droit[9] = 'x';
	printf("Modes: %s\n", droit);

	printf("Nombre de liens: %hu\n", b->st_nlink);
	uid = getpwuid(b->st_uid);
	printf("Proprietaire: %s\n", uid->pw_name);
	grp = getgrgid(b->st_gid);
	printf("Groupe: %s\n", grp->gr_name);
	printf("Taille : %lld octets\n", b->st_size);
	printf("Date de derniere modification: %s", ctime(&(b->st_mtime)));
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
