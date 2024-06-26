/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/26 17:04:10 by lbehr            ###   ########.fr       */
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

typedef struct s_game_map_dimension
{
	int						height;
	int						*width;
}							t_game_map_dimension;

typedef struct s_game_map_info
{
	char					*pathmap;
	t_game_map_texture		map_texture;
	int						color_ceiling;
	int						color_floor;
	t_game_map_dimension	map_dim;
}							t_game_map_info;

typedef struct s_game
{
	void					*mlx_ptr;
	void					*win_ptr;
	char					**area;
	t_game_map_info			map_info;
	t_game_pos				pos;
}							t_game;

// mapChecker.c
int							checkExtension(char *str, char *extension);

// mapCheckerInput.c
int							checkAll(t_game *game);
int							checkOtherChar(t_game *game);
int							checkWall(t_game *game);
int							checkPlayer(t_game *game);

// mapColor.c
int							create_rgb(int *tab);
int							recoColorC(t_game *game);
int							recoColorF(t_game *game);
int							addvalueColor(char *line, int *color);
int							*setColorTab(char **color);

// mapCreate.c
int							createArea(t_game *game);
void						putpos(t_game *game, int x, int y);

// mapSize.c
int							calculateMapSize(char *pathmap, t_game *game);

// mapTexture.c
int							recomapinfo(t_game *game);
int							recotexturen(t_game *game);
int							recotexturee(t_game *game);
int							recotextures(t_game *game);
int							recotexturew(t_game *game);

// mapUtils.c
int							addvaluetexture(char *line, char **map_texture);

// initTexture.c
void						inittexture(t_game *game);

// get_next_line.c

char						*get_next_line(int fd);

// utils.c
int							error(char *text);
int							strlenno(char *str);

// utilsfree.c
void						freeend(t_game *game);
int							freeandreturn(char *str);
void						freetab(char **str);
void						freeifnotnull(t_game_map_texture *texture);

#endif