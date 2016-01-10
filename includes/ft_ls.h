
#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>

# define MAJOR 0XFF000000
# define OP "Ralrt"

//#define DEBUG

// Arguments
typedef struct		s_ft_ls
{
	char			op_R;		// Liste des option
	char			op_a;		// Liste des option
	char			op_l;		// Liste des option
	char			op_r;		// Liste des option
	char			op_t;		// Liste des option
	char			**path;		// Liste des chemin passer en param
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

}					t_elem;

// init
void	ft_init_t_ft_ls(t_ft_ls *data);
void	ft_init_t_elem(t_elem *elem);

// droit des fichier
char	*ft_modeoffile(mode_t mode);

// Format date
char	*ft_format_date(time_t date);

// Trie
void	ft_sort_elem(t_elem **str, int size);
void	ft_sort_str(char ***str, int size);

// Error
int		ft_error(int nb, char *str);

// Dir
t_elem	*ft_readdir(char *fpath, char *path);

// option
char	*ft_get_arg(t_ft_ls *data, char **lst, int nb);
void	ft_set_op(char *op, t_ft_ls *data);
char	*ft_format_path(char *str);
int		ft_check_op(char *op);
int		ft_is_dir(char *path, char *fpath);

// browse
void	ft_browse(t_ft_ls data);

// free
void	ft_free_lst(t_ft_ls data);

void	print(t_ft_ls data, t_elem **elem, char *path);

#endif

// write
// opendir
// readdir
// closedir
// stat
// lstat
// getpwuid
// getgrgid
// listxattr
// getxattr
// time
// ctime
// readlink
// malloc
// free
// perror
// strerror
// exit


/* -------  for stat -----
 *    struct stat {  // when _DARWIN_FEATURE_64_BIT_INODE is NOT defined
 *       dev_t    st_dev;    //  device inode resides on
 *       ino_t    st_ino;    //  inode's number
 *       mode_t   st_mode;   //  inode protection mode
 *       nlink_t  st_nlink;  //  number of hard links to the file
 *       uid_t    st_uid;    //  user-id of owner
 *       gid_t    st_gid;    //  group-id of owner
 *       dev_t    st_rdev;   //  device type, for special file inode
 *       struct timespec st_atimespec; //  time of last access
 *       struct timespec st_mtimespec; //  time of last data modification
 *       struct timespec st_ctimespec; //  time of last file status change
 *       off_t    st_size;   //  file size, in bytes
 *       quad_t   st_blocks; //  blocks allocated for file
 *       u_long   st_blksize;//  optimal file sys I/O ops blocksize
 *       u_long   st_flags;  //  user defined flags for file
 *       u_long   st_gen;    //  file generation number
 *   };
 */

/* ------ for getpwuid -----
 *  struct passwd {
 *          char    *pw_name;      //  user name
 *          char    *pw_passwd;    //  encrypted password
 *          uid_t   pw_uid;        //  user uid
 *          gid_t   pw_gid;        //  user gid
 *          time_t  pw_change;     //  password change time
 *          char    *pw_class;     //  user access class
 *          char    *pw_gecos;     //  Honeywell login info
 *          char    *pw_dir;       //  home directory
 *          char    *pw_shell;     //  default shell
 *          time_t  pw_expire;     //  account expiration
 *          int     pw_fields;     //  internal: fields filled in
 *  };
 */

/* -------- for getgrgid ------
 *
 *  struct group {
 *          char    *gr_name;      //  group name
 *          char    *gr_passwd;    //  group password
 *          gid_t   gr_gid;        //  group id
 *          char    **gr_mem;      //  group members
 *  };
 */

/*	man chmod
 *   #define S_IRUSR 0000400    // R for owner
 *   #define S_IWUSR 0000200    // W for owner
 *   #define S_IXUSR 0000100    // X for owner
 *
 *   #define S_IRGRP 0000040    // R for group
 *   #define S_IWGRP 0000020    // W for group
 *   #define S_IXGRP 0000010    // X for group
 *
 *   #define S_IROTH 0000004    // R for other
 *   #define S_IWOTH 0000002    // W for other
 *   #define S_IXOTH 0000001    // X for other
*/

/*
#define __DARWIN_STRUCT_DIRENTRY { \
103 >   __uint64_t  d_ino;      // file number of entry 
104 >   __uint64_t  d_seekoff;  // seek offset (optional, used by servers)
105 >   __uint16_t  d_reclen;   // length of this record
106 >   __uint16_t  d_namlen;   // length of string in d_name
107 >   __uint8_t   d_type;     // file type, see below
108 >   char      d_name[__DARWIN_MAXPATHLEN]; // entry name (up to MAXPATHLEN bytes)
109 }

123 #define>DT_UNKNOWN>  0
124 #define>DT_FIFO>>    1
125 #define>DT_CHR> >    2
126 #define>DT_DIR> >    4
127 #define>DT_BLK> >    6
128 #define>DT_REG> >    8
129 #define>DT_LNK> >   10
130 #define>DT_SOCK>>   12
131 #define>DT_WHT> >   14
 */
