
#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

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

/*
 *   #define S_IRWXU 0000700    // RWX mask for owner
 *   #define S_IRUSR 0000400    // R for owner
 *   #define S_IWUSR 0000200    // W for owner
 *   #define S_IXUSR 0000100    // X for owner
 *
 *   #define S_IRWXG 0000070    // RWX mask for group
 *   #define S_IRGRP 0000040    // R for group
 *   #define S_IWGRP 0000020    // W for group
 *   #define S_IXGRP 0000010    // X for group
 *
 *   #define S_IRWXO 0000007    // RWX mask for other
 *   #define S_IROTH 0000004    // R for other
 *   #define S_IWOTH 0000002    // W for other
 *   #define S_IXOTH 0000001    // X for other
 *
 *   #define S_ISUID 0004000    // set user id on execution
 *   #define S_ISGID 0002000    // set group id on execution
 *   #define S_ISVTX 0001000    // save swapped text even after use
*/
