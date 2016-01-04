// Commencer par -l -R

#include "ft_ls.h"

int main(int ac, const char **av)
{
	struct stat *b;
	struct passwd *uid;
	struct group *grp;

	b = (struct stat *)malloc(sizeof(struct stat *));
	if (stat(av[1], b) == -1)
	{
		printf("error\n");
		return (-1);
	}
	printf("Nom: %s\n", av[1]);
	printf("Type: %u\n", b->st_flags);
	printf("Modes: %hu\n", b->st_mode);
	printf("Nombre de liens: %hu\n", b->st_nlink);
	uid = getpwuid(b->st_uid);
	printf("Proprietaire: %s\n", uid->pw_name);
	grp = getgrgid(b->st_gid);
	printf("Groupe: %s\n", grp->gr_name);
	printf("Taille : %lld octets\n", b->st_size);
	printf("Date de derniere modification: %ld\n", b->st_mtime);
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
