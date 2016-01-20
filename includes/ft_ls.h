
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
	struct s_elem	*next;
}					t_elem;

// elem
t_elem				*ft_elem_new(char *name);
void				ft_init_t_elem(t_elem *elem);
t_elem				*ft_elem_insert(t_elem **aelem, char *name, char r);
void				ft_free_elem(t_elem **elem);

// data
void				ft_init_t_ft_ls(t_ft_ls *data);
void				ft_free_lst(t_ft_ls *data);

// str
void				ft_sort_str(char ***str, int size, int r);

// error
int					ft_error(int nb, char *str);

//read
t_elem				*ft_readdir(char *fpath, char *path, char r);

// arg
char				*ft_get_arg(t_ft_ls *data, char **lst, int nb);
void				ft_set_op(char *op, t_ft_ls *data);
int					ft_check_op(char *op);
int					ft_check_arg(t_ft_ls data);

//format
char				*ft_format_path(char *str);
char				*ft_format_date(time_t date);

int					ft_is_dir(char *path);

void				ft_browse(t_ft_ls *data);

// print
void				ft_print(t_ft_ls data, t_elem **elem, char *path, int t);

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
