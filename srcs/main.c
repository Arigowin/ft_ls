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
void	printone(t_elem elem, size_t *size, int rdev)
{
	// 0 : nlink
	// 1 : uid
	// 2 : grp
	// 3 : size
	size_t	i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : printone\n");
#endif

	ft_putstr(elem.droit);
	ft_putstr(" ");
	i = 0;
	while (i < size[0] - ft_strlen(elem.nlink))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(elem.nlink);
	ft_putstr(" ");
	ft_putstr(elem.uid);
	i = 0;
	while (i < size[1] - ft_strlen(elem.uid))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr("  ");
	ft_putstr(elem.grp);
	i = 0;
	while (i < size[2] - ft_strlen(elem.grp))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr("  ");
	if (elem.size != NULL)
	{
		i = 0;
		if (rdev)
		{
			while (i < size[4] + size[3])
			{
				ft_putchar(' ');
				i++;
			}
		}
		else
		{
			while (i < size[3] - ft_strlen(elem.size))
			{
				ft_putchar(' ');
				i++;
			}
		}
		ft_putstr(elem.size);
	}
	else
	{
		i = 0;
		while (i < size[3] - ft_strlen(elem.rdevmineur) - 1)
		{
			ft_putchar(' ');
			i++;
		}
		ft_putstr(elem.rdevmineur);
		ft_putstr(", ");
		i = 0;
		while (i < size[4] - ft_strlen(elem.rdevmajeur))
		{
			ft_putchar(' ');
			i++;
		}
		ft_putstr(elem.rdevmajeur);
	}
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
	char		*tmp2;
	size_t		sizemax[5] = {0, 0, 0, 0, 0};

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : print\n");
#endif

	tmp2 = NULL;
	i = 0;
	while(i < (*elem)[0].nbelem)
	{
		if ((*elem)[i].name != NULL)
		{
			if (lstat(ft_strjoin(path, (*elem)[i].name), &st) == -1)
				exit (ft_error(1, (*elem)[i].name));

			(*elem)[i].droit = ft_modeoffile(st.st_mode);

			tmp = ft_itoa(st.st_nlink);
			printf("%zu\t%s\n", sizemax[0], tmp);
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

			if ((*elem)[i].droit[0] != 'c' && (*elem)[i].droit[0] != 'b')
			{
				tmp = ft_itoa(st.st_size);
				if (sizemax[3] < ft_strlen(tmp))
				{
					sizemax[3] = ft_strlen(tmp);
				}
				(*elem)[i].size = tmp;
			}
			else
			{
				tmp = ft_itoa((st.st_rdev & MAJOR) >> 24);
				tmp2 = ft_itoa((st.st_rdev & ~MAJOR));
				if (sizemax[3] < ft_strlen(tmp))
					sizemax[3] = ft_strlen(tmp);
				if (sizemax[4] < ft_strlen(tmp2))
					sizemax[4] = ft_strlen(tmp2);
				(*elem)[i].rdevmineur = tmp;
				(*elem)[i].rdevmajeur = tmp2;
			}

			(*elem)[i].date = ft_format_date(st.st_mtime);
		}
		i++;
	}
	i = 0;
	while (i < (*elem)[0].nbelem)
	{
		if ((*elem)[i].name != NULL && (data.op_a || (*elem)[i].name[0] != '.'))
		{
			if (tmp2 == NULL)
				printone((*elem)[i], sizemax, 0);
			else
				printone((*elem)[i], sizemax, 1);
		}
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
	elem->rdevmineur = NULL;
	elem->rdevmajeur = NULL;
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

	//ft_free_lst(data);

	return (0);
}
