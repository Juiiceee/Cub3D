# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 15:57:01 by lbehr             #+#    #+#              #
#    Updated: 2024/06/30 15:00:26 by lbehr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D
SRC_DIR		:= src
OBJ_DIR		:= obj
SRCS		:= gnl/get_next_line.c map/mapCheckInput.c map/mapChecker.c map/mapColor.c map/mapCreate.c map/mapSize.c map/mapTexture.c map/mapUtils.c map/mapAreaCreate.c init/initTexture.c main.c utils/utils.c utils/utilsfree.c
#alias mc='find ./src -name "*.c" | tr "\n" " " | sed -e "s#\\./src/##g" -e "s/ $//" | xclip -selection clipboard'
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			:= cc
MINI		:= -lX11 -lXext Include/minilibx-linux/libmlx_Linux.a
CFLAGS		:= -Wall -Wextra -Werror -g3
CPPFLAGS	:= -MMD -MP -I Include
MLX_PATH	:= Include/minilibx-linux
DEPS		:= $(OBJS:.o=.d)
RM			:= rm -rf
DIR_DUP		= mkdir -p $(@D)
LIBFT		:= libft

all		: $(MLX_PATH) $(NAME)

$(MLX_PATH):
	git clone git@github.com:42Paris/minilibx-linux.git Include/minilibx-linux

$(NAME)	:	$(OBJS)
	$(DIR_DUP)
	@make -C $(LIBFT) --no-print-directory
	@make -C $(MLX_PATH) --no-print-directory
	$(CC) $(OBJS) $(LIBFT)/libft.a $(MINI) -o $(NAME) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

-include $(DEPS)

bonus	:

clean	:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT) clean --no-print-directory

fclean	:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean --no-print-directory
	
git	:	fclean
	$(RM) $(MLX_PATH)
	$(RM) bin

re		:	fclean all
	make -C $(LIBFT) re --no-print-directory

rall	:	git all

.PHONY: all clean fclean git re rall bonus