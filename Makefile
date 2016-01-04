# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/03 10:52:20 by dolewski          #+#    #+#              #
#    Updated: 2016/01/04 11:13:53 by dolewski         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
LFTHPATH =	$(LIBPATH)/includes

CFLAGS = -g -Wall -Werror -Wextra -I $(HPATH) -I $(LFTHPATH)
LIBS = -L $(LIBPATH) -lft

SRC = main.c

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

.PHONY: all clean fclean re

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

# little memo
# $@ = rule's name
# $^ = all the rule dependecies
# $< = only the first dependence

# Color for c
#   NRM  "\033[0m"
#   RED  "\033[31m"
#   GRN  "\033[32m"
#   YEL  "\033[33m"
#   BLU  "\033[34m"
#   MAG  "\033[35m"
#   CYN  "\033[36m"
#   WHT  "\033[37m"
