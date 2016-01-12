
#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>

# define MAJOR 0XFF000000
# define OP "Ralrt"

#define BUFF_SIZE 1024

//#define DEBUG

typedef struct		s_ft_ls
{
	char			op_R;
	char			op_a;
	char			op_l;
	char			op_r;
	char			op_t;
	char			**path;
	int				nb_path;
}					t_ft_ls;

typedef struct		s_elem
{
	char			*name;
	char			type;
	int				nbelem;
	char			*droit;
	char			*nlink;
	char			*uid;
	char			*grp;
	char			*size;
	char			*date;
	char			*sec_date;
	char			*rdevmineur;
	char			*rdevmajeur;
	char			*link;

}					t_elem;

void	ft_init_t_ft_ls(t_ft_ls *data);
void	ft_init_t_elem(t_elem *elem);
char	*ft_modeoffile(mode_t mode);
char	*ft_format_date(time_t date);
void	ft_sort_elem(t_elem **str, int size, int r);
void	ft_sort_elem_date(t_elem **str, int size, int r, int a);
void	ft_sort_str(char ***str, int size, int r);
int		ft_error(int nb, char *str);
t_elem	*ft_readdir(char *fpath, char *path, t_ft_ls data);
char	*ft_get_arg(t_ft_ls *data, char **lst, int nb);
void	ft_set_op(char *op, t_ft_ls *data);
char	*ft_format_path(char *str);
int		ft_check_op(char *op);
int		ft_is_dir(char *path, char *fpath);
void	ft_browse(t_ft_ls data);
void	ft_free_lst(t_ft_ls *data);
void	ft_free_elem(t_elem **elem);
void	ft_print(t_ft_ls data, t_elem **elem, char *path);

#endif
