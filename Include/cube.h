/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/17 17:55:15 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define WHITE 0xFFFFFF
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef enum e_bool
{
	False,
	True
}							t_bool;

typedef struct s_game_mesure
{
	int						line;
	int						column;
}							t_game_mesure;

typedef struct s_game_pos
{
	float					posx;
	float					posy;
	float					dirx;
	float					diry;
	float					planex;
	float					planey;
}							t_game_pos;

typedef struct s_game_map_texture
{
	char					*north;
	char					*east;
	char					*south;
	char					*west;
}							t_game_map_texture;

typedef struct s_game_map_color
{
	char					*green;
	char					*blue;
	char					*red;
}							t_game_map_color;

typedef struct s_game_map_dimension
{
	int						height;
	int						width;
	char					**area;
}							t_game_map_dimension;

typedef struct s_game_map_info
{
	char					*pathmap;
	t_game_map_texture		map_texture;
	t_game_map_color		color_ceiling;
	t_game_map_color		color_floor;
	t_game_map_dimension	map_dim;
}							t_game_map_info;

typedef struct s_game
{
	void					*mlx_ptr;
	void					*win_ptr;
	char					**area;
	t_game_map_info			map_info;
	t_game_mesure			mesure;
	t_game_pos				pos;
}							t_game;

// mapChecker.c

int							checkExtension(char *str);
int							checkSize(t_game game);

// mapCheckerInput.c

int							checkAll(t_game *game);
int							checkOtherChar(t_game *game);
int							checkWall(t_game *game);
int							checkPlayer(t_game *game);

// mapCreate.c

void						inputArea(char *map, t_game *game);
char						**createArea(int ligne, size_t colonne);
void						putpos(t_game *game, int x, int y);

// mapSize.c

int							calculateMapSize(char *map, int *colonne);

// mapUtils.c

int							error(char *text);
int							strlenno(char *str);
int							freeandreturn(char *str);
void						freetab(t_game *game);
int							addvaluetexture(int i, char *line, char *map_texture);

// get_next_line.c

char						*get_next_line(int fd);

#endif