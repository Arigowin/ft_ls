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
void	printone(t_elem elem, size_t *size)
{
	// 0 : nlink
	// 1 : uid
	// 2 : grp
	// 3 : size
	size_t	i;

	ft_putstr(elem.droit);
	ft_putstr("  ");
	i = 0;
	while (i < size[0] - ft_strlen(elem.nlink))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(elem.nlink);
	ft_putstr(" ");
	i = 0;
	while (i < size[1] - ft_strlen(elem.uid))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(elem.uid);
	ft_putstr("  ");
	i = 0;
	while (i < size[2] - ft_strlen(elem.grp))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(elem.grp);
	ft_putstr("  ");
	i = 0;
	while (i < size[3] - ft_strlen(elem.size))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(elem.size);
	ft_putstr(" ");
	ft_putstr(elem.date);
	ft_putstr(" ");
	ft_putstr(elem.name);
	// si lien symbolique afficher le lien
	ft_putstr("\n");

}

void	print(t_ft_ls data, t_elem **elem, char *path)
{
	struct stat st;
	int			i;
	char		*tmp;
	size_t		sizemax[4] = {0, 0, 0, 0};

	i = 0;
	while(i < (*elem)[0].nbelem)
	{
		if (lstat(ft_strjoin(path, (*elem)[i].name), &st) == -1)
			exit (ft_error(1, (*elem)[i].name));

		(*elem)[i].droit = ft_modeoffile(st.st_mode);

		tmp = ft_itoa(st.st_nlink);
		if (sizemax[0] < ft_strlen(tmp))
			sizemax[0] = ft_strlen(tmp);
		(*elem)[i].nlink = tmp;

		tmp = (getpwuid(st.st_uid))->pw_name;
		if (sizemax[1] < ft_strlen(tmp))
			sizemax[1] = ft_strlen(tmp);
		(*elem)[i].uid = tmp;

		tmp = (getgrgid(st.st_gid))->gr_name;
		if (sizemax[2] < ft_strlen(tmp))
			sizemax[2] = ft_strlen(tmp);
		(*elem)[i].grp = tmp;

		tmp = ft_itoa(st.st_size);
		if (sizemax[3] < ft_strlen(tmp))
			sizemax[3] = ft_strlen(tmp);
		(*elem)[i].size = tmp;

		(*elem)[i].date = ft_format_date(st.st_mtime);
		i++;
	}
	i = 0;
	while (i < (*elem)[0].nbelem)
	{
		if (data.op_a || (*elem)[i].name[0] != '.')
			printone((*elem)[i], sizemax);
		i++;
	}
}

void	ft_init_t_ft_ls(t_ft_ls *data)
{
	data->path = NULL;
	data->op_R = 0;
	data->op_a = 0;
	data->op_l = 0;
	data->op_r = 0;
	data->op_t = 0;
	data->nb_path = 0;
}

void	ft_init_t_elem(t_elem *elem)
{
	elem->name = NULL;
	elem->droit = NULL;
	elem->nlink = NULL;
	elem->uid = NULL;
	elem->grp = NULL;
	elem->size = NULL;
	elem->date = NULL;
	elem->type = 0;
	elem->nbelem = 0;
}

int main(int ac, char **av)
{
	t_ft_ls		data;
	char		*op;

	ft_init_t_ft_ls(&data);

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : main\n");
#endif

	op = ft_get_arg(&data, av, ac);
	ft_set_op(op, &data);
	if (data.nb_path > 1)
		ft_sort_str(&(data.path), data.nb_path);

	ft_browse(data);

//	ft_free_lst(data);

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
