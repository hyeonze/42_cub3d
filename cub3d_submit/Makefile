# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By:      <    @student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 11:36:43 by                   #+#    #+#              #
#    Updated: 2021/02/08 12:34:31 by                  ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = ./libft/libft.a

CC = gcc
INCS = -I./includes -I./libft -I./mlx
INCLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Llibft -lft
CFLAGS = -Wall -Werror -Wextra $(INCS)
LIBFT = ./libft

SRCS = ./srcs/main.c\
		./srcs/check_map_validity.c\
		./srcs/get_next_line.c\
		./srcs/init.c\
		./srcs/key_press_event.c\
		./srcs/parse_before_map.c\
		./srcs/parse_check_map.c\
		./srcs/load_image_texture.c\
		./srcs/cast_floor_ceiling.c\
		./srcs/utils.c\
		./srcs/raycasting_utils.c\
		./srcs/draw.c\
		./srcs/get_wall_info.c\
		./srcs/sprite_utils.c\
		./srcs/sprite_utils2.c\
		./srcs/main_loop_hook.c\
		./srcs/save_bmp_file.c\
		./srcs/free_exit.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(INCLIB)

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: test bonus all clean fclean re
