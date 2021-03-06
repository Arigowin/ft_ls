CC =	/usr/bin/clang
RM =	/bin/rm
MAKE =	/usr/bin/make
MKDIR =	/bin/mkdir

NAME = ft_ls

ROOT =		$(shell /bin/pwd)
OPATH =		$(ROOT)/objs
CPATH =		$(ROOT)/srcs
HPATH =		$(ROOT)/includes
LIBPATH =	$(ROOT)/libft
LIBHPATH =	$(LIBPATH)/includes

CFLAGS = -g -Wall -Werror -Wextra -I $(HPATH) -I $(LIBHPATH)
LIBS = -L $(LIBPATH) -lft

SRC = ft_ls_browse.c \
	ft_ls_browse_bis.c \
	ft_ls_check.c \
	ft_ls_elem.c \
	ft_ls_error.c \
	ft_ls_format.c \
	ft_ls_free.c \
	ft_ls_get_info.c \
	ft_ls_get_info_bis.c \
	ft_ls_init.c \
	ft_ls_modeoffile.c \
	ft_ls_option.c \
	ft_ls_print.c \
	ft_ls_print_bis.c \
	ft_ls_readdir.c \
	ft_ls_sort.c \
	main.c

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

.PHONY: all clean fclean re lib.fclean

all: $(OPATH) $(NAME)

$(NAME): $(OFILES)
	@echo "$(NAME) : Building Libft"
	@$(MAKE) -C $(LIBPATH)
	@echo "$(NAME) : Building $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\033[32mDone !\033[0m"

$(OPATH)/%.o: $(CPATH)/%.c
	@echo "$(NAME) : Creating file $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OPATH):
	@echo "$(NAME) : Creating objs directory"
	@$(MKDIR) $@

clean:
	@echo "$(NAME) : Deleting objs"
	@$(RM) -rf $(OPATH)

fclean: clean lib.fclean
	@echo "$(NAME) : Deleting $(NAME)"
	@$(RM) -f $(NAME)
	@echo "\033[32mDone !\033[0m"

lib.fclean:
	@$(MAKE) fclean -C $(LIBPATH)

re: fclean all
