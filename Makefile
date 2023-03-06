# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kwpark <kwpark@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 15:24:20 by kwpark            #+#    #+#              #
#    Updated: 2023/03/06 09:48:02 by kwpark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft

MLX = minilibx

SOURCES = 	src/check_color.c \
			src/check_dir.c \
			src/check_wall.c \
			src/cub3d_utils.c \
			src/cub3d.c \
			src/ft_parse.c \
			src/init.c \
			src/key_press.c \
			src/load_map.c \
			src/raycasting_utils.c \
			src/raycasting.c \
			src/test.c \
			src/utils.c

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(MLX)
	@cp libft/libft.a ./
	@cp minilibx/libmlx.a ./
	$(CC) $(CFLAGS) -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) libft.a libmlx.a

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS) libft.a libmlx.a
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX)

re: fclean all

.PHONY : all, clean, fclean, re, bonus