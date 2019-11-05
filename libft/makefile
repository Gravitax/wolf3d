# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 11:17:40 by maboye            #+#    #+#              #
#    Updated: 2019/07/31 11:57:08 by maboye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

HEADER	=	libft.h

#DIR LIST
D_MATHS	=	./maths
D_MEM	=	./mem
D_PRINT	=	./print
D_STR	=	./str
D_TAB	=	./tab

#SRC LIST
S_MATHS	=	ft_isprime.c\
			ft_power.c\
			ft_sqrt.c

S_MEM	=	ft_memalloc.c\
			ft_memcpy.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memdel.c\
			ft_memmove.c\
			ft_memset.c

S_PRINT	=	ft_printf.c\
			ft_putchar.c\
			ft_putchar_fd.c\
			ft_putendl.c\
			ft_putendl_fd.c\
			ft_putnbr.c\
			ft_putnbr_fd.c\
			ft_putstr.c\
			ft_putstr_fd.c\
			my_printf.c\
			my_putchar_fd.c\
			my_putendl_fd.c\
			my_putnbr_fd.c\
			my_putstr_fd.c

S_STR	=	ft_abs.c\
			ft_atoi_base.c\
			ft_atoi.c\
			ft_bzero.c\
			ft_intlen.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isdigit.c\
			ft_ishexa.c\
			ft_islower.c\
			ft_isprint.c\
			ft_isspace.c\
			ft_isupper.c\
			ft_itoa.c\
			ft_readfile.c\
			ft_realloc.c\
			ft_splitwspc.c\
			ft_strcat.c\
			ft_strchr.c\
			ft_strclen.c\
			ft_strcmp.c\
			ft_strcpy.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strfjoin.c\
			ft_strjoin.c\
			ft_strlen.c\
			ft_strncat.c\
			ft_strncmp.c\
			ft_strncpy.c\
			ft_strnew.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strsplit.c\
			ft_strstr.c\
			ft_strsub.c\
			ft_strtrim.c\
			ft_swap.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_wordcount.c\
			get_next_line.c

S_TAB	=	ft_tabaddelem.c\
			ft_tabdup.c\
			ft_tabfree.c\
			ft_tablen.c\
			ft_tabmerge.c\
			ft_tabprint.c

SRC		=	$(addprefix $(D_MATHS)/,$(S_MATHS))\
			$(addprefix $(D_MEM)/,$(S_MEM))\
			$(addprefix $(D_PRINT)/,$(S_PRINT))\
			$(addprefix $(D_STR)/,$(S_STR))\
			$(addprefix $(D_TAB)/,$(S_TAB))

OBJ 	=	$(SRC:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INCLUDE	=	-I .

BLACK	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
TUR		=	\033[36m
WHITE	=	\033[37m
END		=	\033[0m

UP 		=	\033[A
CUT 	=	\033[K

all:		$(NAME)

%.o:		%.c
			@echo "${TUR}compiling [$@] ...${END}"
			@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
			@printf "$(UP)$(CUT)"

$(NAME):	$(OBJ) $(HEADER)
			@ar rcs $(NAME) $(OBJ)

clean:
			@/bin/rm -rf $(OBJ)

fclean:		clean
			@/bin/rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
