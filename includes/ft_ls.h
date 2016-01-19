
#ifndef FT_LS_H

# define FT_LS_H
# define MAJOR 0XFF000000
# define OP "1Ralrt"
# define BUFF_SIZE 1024

# include <sys/types.h>

//#define DEBUG

typedef struct		s_ft_ls
{
	char			op_recu;
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
	int				sec_date;
	char			*rdevmineur;
	char			*rdevmajeur;
	char			*link;

}					t_elem;

void				ft_init_t_ft_ls(t_ft_ls *data);
void				ft_init_t_elem(t_elem *elem);

void				ft_sort_elem(t_elem **str, int size, int r);
void				ft_sort_elem_date(t_elem **str, int size, int r, int a);
void				ft_sort_str(char ***str, int size, int r);

int					ft_error(int nb, char *str);

t_elem				*ft_readdir(char *fpath, char *path);

char				*ft_get_arg(t_ft_ls *data, char **lst, int nb);
void				ft_set_op(char *op, t_ft_ls *data);
int					ft_check_op(char *op);
int					ft_check_arg(t_ft_ls data);

char				*ft_format_path(char *str);
char				*ft_format_date(time_t date);

int					ft_is_dir(char *path);

void				ft_browse(t_ft_ls *data);

void				ft_free_lst(t_ft_ls *data);
void				ft_free_elem(t_elem *elem);

void				ft_print(t_ft_ls data, t_elem **elem, char *path);

char				*ft_modeoffile(mode_t mode);

size_t				ft_get_info(char *path, t_elem *elem, size_t sizemax[]);
int					ft_get_info_nlink(t_elem *elem, nlink_t nlink, size_t size);
int					ft_get_info_pw(t_elem *elem, uid_t uid, size_t size);
int					ft_get_info_gr(t_elem *elem, gid_t gid, size_t size);
int					ft_get_info_size(t_elem *elem, off_t s, size_t size);
int					ft_get_info_rdev(t_elem *elem, dev_t rdev, size_t *size);
void				ft_get_info_date(t_elem *elem, time_t mtime);
void				ft_get_info_link(t_elem *elem, char *path);

#endif
