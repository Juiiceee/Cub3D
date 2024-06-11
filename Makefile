# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 15:57:01 by lbehr             #+#    #+#              #
#    Updated: 2024/06/11 09:00:55 by lbehr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D
SRC_DIR		:= src
OBJ_DIR		:= obj
SRCS		:= main.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			:= cc
MINI		:= -lX11 -lXext Include/minilibx-linux/libmlx_Linux.a -I Include
CFLAGS		:= -Wall -Wextra -Werror -g3
MLX_PATH	:= Include/minilibx-linux
RM			:= rm -rf
DIR_DUP     = mkdir -p $(@D)

all		: $(MLX_PATH) $(NAME)

$(MLX_PATH):
	git clone git@github.com:42Paris/minilibx-linux.git Include/minilibx-linux

$(NAME)	:	$(OBJS)
	$(DIR_DUP)
	make -C $(MLX_PATH) --no-print-directory
	$(CC) $(OBJS) $(MINI) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) -c $< $(CFLAGS) -o $@

bonus	:	all

clean	:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean	:	clean
	$(RM) $(NAME)
	
git	:	fclean
	$(RM) $(MLX_PATH)
	$(RM) bin

re		:	fclean all

rall	:	git all

.PHONY: all clean fclean git re rall bonus