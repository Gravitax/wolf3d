# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/31 12:01:33 by maboye            #+#    #+#              #
#    Updated: 2019/12/14 01:08:18 by saneveu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

# project
NAME	=	wolf3d
OS		=	$(shell uname)

# directories
SRCDIR	=	./srcs
INCDIR	=	./includes
OBJDIR	=	./obj

# src / obj files
SRC		=	astar_list.c \
			astar.c \
			datagame.c \
			display.c \
			events.c \
			game_over.c \
			grenada.c \
			main.c \
			minimap.c \
			monsters.c \
			mouse_events.c \
			movements.c \
			nodes.c \
			objects.c \
			raycasting.c \
			shoot.c \
			spawner.c \
			sprites.c \
			tools.c \
			tools2.c\
			weapons.c \
			wolf3d.c  \
			pause.c \
			tool_render.c \
			minimap_monster.c \
			floor.c \
			draw_ray.c

INC		=	wolf3d.h

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
HEADER	=	$(addprefix $(INCDIR)/,$(INC))

# compiler
CC		=	gcc
CFLAGS	=	#-Wall -Wextra -Werror #-g3 -fsanitize=address

ifeq ($(OS), Linux)
	SDL		=	-lSDL2-2.0 -lSDL2_ttf
	DIRSDL	=	
else
	SDL		=	-F ~/Library/Frameworks -framework SDL2 -framework SDL2_ttf
	DIRSDL	=	./SDL2.framework/Headers
endif 

# ft library
FT		=	./libft/
FT_LIB	=	$(addprefix $(FT),libft.a)

all: 		obj $(FT_LIB) $(NAME)

obj:
			mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(HEADER)
			@echo "${TUR}compiling [$@] ...${END}"
			@$(CC) $(CFLAGS) -I $(INCDIR) -c -o $@ $<
			#-I $(DIRSDL)
			@printf "$(UP)$(CUT)"

$(FT_LIB):
			@$(MAKE) -C $(FT)
			@echo "${GREEN}[LIBRARY COMPILED]${END}"

$(NAME):	$(OBJ) $(FT_LIB)
			@$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) $(SDL) -lm -lpthread -o $@
			@echo "${GREEN}[$@ COMPILED]${END}"

clean:
			@/bin/rm -rf $(OBJDIR)
			@$(MAKE) -C $(FT) clean
			@echo "${PURPLE}[.o deleted]${END}"

#$(MAKE) -C $(MLX) clean

fclean:		clean
			@/bin/rm -rf $(NAME)
			@$(MAKE) -C $(FT) fclean
			@echo "${RED}[$(NAME) deleted]${END}"
			@echo "${RED}[$(LIB) deleted]${END}"

re:			fclean all

.PHONY:		all clean fclean re
