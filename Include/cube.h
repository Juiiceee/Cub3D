/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/01 14:02:31 by lbehr            ###   ########.fr       */
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

typedef enum e_return
{
	SUCCESS,
	FAILURE
} t_return ;

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

typedef struct s_game_area_dimension
{
	int						height;
	int						width;
}							t_game_area_dimension;

typedef struct s_game_map_info
{
	char					*pathmap;
	t_game_map_texture		map_texture;
	int						color_ceiling;
	int						color_floor;
	int						heightmap;
	t_game_area_dimension	area_dim;
}							t_game_map_info;

typedef struct s_game
{
	void					*mlx_ptr;
	void					*win_ptr;
	char					**map;
	char					**area;
	t_game_map_info			map_info;
	t_game_pos				pos;
}							t_game;

// mapAreaCreate.c
int							recoarea(t_game *game);
int							checkifarea(t_game *game, int *start, int *end);
int							createarea(t_game *game, int start, int end);
void						changevalue(t_game *game);
void						getareainfo(t_game *game, int start, int end);

// mapChecker.c
int							checkextension(char *str, char *extension);

// mapCheckerInput.c
int							checkall(t_game *game);
int							checkotherchar(t_game game);
int							checkwall(t_game game);
int							checkplayer(t_game *game);

// mapColor.c
int							create_rgb(int *tab);
int							getcolor_c(t_game *game);
int							getcolor_f(t_game *game);
int							addvaluecolor(char *line, int *color);
int							*setcolortab(char **color);

// mapCreate.c
int							createmap(t_game *game);
void						putpos(t_game *game, int x, int y);

// mapSize.c
int							calculatemapsize(char *pathmap, t_game *game);

// mapTexture.c
int							getmapinfo(t_game *game);
int							gettexturen(t_game *game);
int							gettexturee(t_game *game);
int							gettextures(t_game *game);
int							gettexturew(t_game *game);

// mapUtils.c
int							addvaluetexture(char *line, char **map_texture);

// init.c
void						initall(t_game *game);
void						inittexture(t_game *game);
void						initvalue(t_game *game);

// get_next_line.c

char						*get_next_line(int fd);

// utils.c
int							error(char *text);
int							strlenno(char *str);
char						*ft_strdup_size(const char *s, int size);
int							ft_atoiAlpha(const char *nptr);

// utilsfree.c
void						freeend(t_game *game);
int							freeandreturn(char *str);
void						freetab(char **str);
void						freeifnotnull(t_game_map_texture *texture);

#endif