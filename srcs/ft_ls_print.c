#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
static void		ft_printone(t_elem elem, size_t *size, int rdev, int op_l)
{
	size_t	i;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : printone\n");
#endif

	if (op_l)
	{
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
				while (i < size[4] + size[3] + 2)
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
			ft_putstr(" ");
			i = 0;
			while (i < size[3] - ft_strlen(elem.rdevmineur))
			{
				ft_putchar(' ');
				i++;
			}
			ft_putstr(elem.rdevmineur);
			ft_putstr(", ");
			i = 0;
			while (i < (size[4] - ft_strlen(elem.rdevmajeur)))
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
		if (elem.link != NULL)
		{
			ft_putstr(" -> ");
			ft_putstr(elem.link);
		}
		ft_putstr("\n");
	}
	else
		ft_putendl(elem.name);
}

void	ft_print(t_ft_ls data, t_elem **elem, char *path)
{
	struct stat st;
	int			i;
	char		*tmp;
	char		*tmp2;
	char		buff[BUFF_SIZE];
	size_t		sizemax[5] = {0, 0, 0, 0, 0};
	size_t		total;
	int			ret;

	// DEBUG
#ifdef DEBUG
	printf("DEBUG : print\n");
#endif

	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	total = 0;
	while(i < (*elem)[0].nbelem)
	{
		if ((*elem)[i].name != NULL &&  (data.op_a || (*elem)[i].name[0] != '.'))
		{
			tmp2 = ft_strjoin(path, (*elem)[i].name);
			if (lstat(tmp2, &st) == -1)
				exit (ft_error(1, (*elem)[i].name));
			ft_strdel(&tmp2);

			(*elem)[i].droit = ft_modeoffile(st.st_mode);

			tmp = ft_itoa(st.st_nlink);
			if (sizemax[0] < ft_strlen(tmp))
				sizemax[0] = ft_strlen(tmp);
			(*elem)[i].nlink = ft_strdup(tmp);
			ft_strdel(&tmp);

			tmp = ft_strdup((getpwuid(st.st_uid))->pw_name);
			if (sizemax[1] < ft_strlen(tmp))
				sizemax[1] = ft_strlen(tmp);
			(*elem)[i].uid = ft_strdup(tmp);
			ft_strdel(&tmp);

			tmp = ft_strdup((getgrgid(st.st_gid))->gr_name);
			if (sizemax[2] < ft_strlen(tmp))
				sizemax[2] = ft_strlen(tmp);
			(*elem)[i].grp = ft_strdup(tmp);
			ft_strdel(&tmp);

			if ((*elem)[i].droit[0] != 'c' && (*elem)[i].droit[0] != 'b')
			{
				tmp = ft_itoa(st.st_size);
				if (sizemax[3] < ft_strlen(tmp))
					sizemax[3] = ft_strlen(tmp);
				(*elem)[i].size = ft_strdup(tmp);
			}
			else
			{
				tmp = ft_itoa((st.st_rdev & MAJOR) >> 24);
				tmp2 = ft_itoa((st.st_rdev & ~MAJOR));
				if (sizemax[3] < ft_strlen(tmp))
					sizemax[3] = ft_strlen(tmp);
				if (sizemax[4] < ft_strlen(tmp2))
					sizemax[4] = ft_strlen(tmp2);
				(*elem)[i].rdevmineur = ft_strdup(tmp);
				(*elem)[i].rdevmajeur = ft_strdup(tmp2);
			}
			ft_strdel(&tmp);
			ft_strdel(&tmp2);

			(*elem)[i].date = ft_strdup(ft_format_date(st.st_mtime));

			(*elem)[i].sec_date = st.st_mtime;

			if ((*elem)[i].droit[0] == 'l')
			{
				if ((ret = readlink(ft_strjoin(path, (*elem)[i].name), buff, BUFF_SIZE)) == -1)
					ft_error(1, path);
				tmp = ft_strsub(buff, 0, ret);
				(*elem)[i].link = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
			total += st.st_blocks;
		}
		i++;
	}
	i = 0;

	if (data.op_l)
	{
		ft_putstr("total ");
		ft_putnbrendl(total);
	}
	ft_sort_elem(elem, (*elem)[0].nbelem, data.op_r);
	if (data.op_t)
		ft_sort_elem_date(elem, (*elem)[0].nbelem, data.op_r, data.op_a);
	while (i < (*elem)[0].nbelem)
	{
		if (data.op_a || (*elem)[i].name[0] != '.')
		{
			if ((*elem)[i].name != NULL)
			{
				if (tmp2 == NULL)
					ft_printone((*elem)[i], sizemax, 0, data.op_l);
				else
					ft_printone((*elem)[i], sizemax, 1, data.op_l);
			}
		}
		i++;
	}
}
