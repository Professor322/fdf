# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlegros <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 18:55:39 by vlegros           #+#    #+#              #
#    Updated: 2019/03/20 23:46:03 by vlegros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = gcc
CHECK_FLAGS = -Wall -Wextra -Werror
COMPILE_FLAGS =  -lmlx -framework OpenGL -framework AppKit
NAME = fdf
ADD_SRC = ./src/
RESOURCES = color_grad.c get_coords.c color_magic.c	init.c conversion_with_check.c key_press.c copy_matrix.c main.c draw_norm_line.c map_manipulation.c event_manipulator.c mouse_press.c ft_paint_matrix.c valid_check.c
SRC_S = $(addprefix $(ADD_SRC), $(RESOURCES))
OBJ = $(SRC_S:.c=.o)
ADD_INC = ./includes/
ADD_LIB_H = ./libft/
ADD_LIBFT = ./libft/libft.a
ADD_MLX = ./minilibx_macos 

all: $(NAME)

$(NAME):  $(OBJ)
	@make  -C ./libft all
	@$(COMPILER) -o $(NAME) $(CHECK_FLAGS) $(COMPILE_FLAGS) $(OBJ) $(ADD_LIBFT) -L $(ADD_MLX)
	@echo ======[Done]======
%.o : %.c
	@echo "$(NAME) >>> Add/Update $<"
	@$(COMPILER) -c -o $@ -I $(ADD_INC) $(CHECK_FLAGS) $<
clean:
	@rm -f $(ADD_SRC)$(OBJ)
	@make  -C ./libft clean
fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean
re: fclean all
