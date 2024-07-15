/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 18:54:06 by mda-cunh         ###   ########.fr       */
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

# define WIN_WIDTH 1280
# define WIN_HEIGHT 960
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
}	t_return;

typedef enum e_bool
{
	False,
	True
}	t_bool;

typedef enum e_keys
{
	W_KEY,
	A_KEY,
	S_KEY,
	D_KEY,
	Larrow_KEY,
	Rarrow_KEY,
	Uarrow_KEY,
	Darrow_KEY,
	ESCAPE
}	t_key;

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_coord_int
{
	int			x;
	int			y;
}					t_coord_int;

typedef struct s_game_mesure
{
	int	line;
	int	column;
}	t_game_mesure;

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

typedef struct s_texture
{
	void					*img;
	char					*data;
	int						width;
	int						height;
	int						bpp;
	int						size_line;
	int						endian;
}	t_texture;

typedef struct s_game_texture
{
	t_texture				north;
	t_texture				west;
	t_texture				east;
	t_texture				south;
}	t_game_texture;

typedef struct s_game_map_info
{
	char					*pathmap;
	t_game_map_texture		map_texture;
	int						color_ceiling;
	int						color_floor;
	int						heightmap;
	t_game_area_dimension	area_dim;
}							t_game_map_info;

typedef struct s_game_ray
{
	double		camera_x;
	t_coord		ray_dir;
	t_coord		side_dis;
	t_coord		delta_dis;
	t_coord_int	map;
	t_coord_int	step;
	double		per_wall_dis;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_coord_int	start_point;
	t_coord_int	end_point;
	int			hit;
	int			side;
	int			tex_x;
	int			tex_width;
	float		wall_x;
	t_texture	sprite;
}	t_game_ray;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**map;
	char			**area;
	int				key[9];
	t_game_mesure	mesure;
	t_game_pos		pos;
	t_game_texture	textures;
	t_texture		img;
	t_game_ray		ray;
	t_game_map_info	map_info;
}	t_game;

// mapAreaCreate.c
int		recoarea(t_game *game);
int		checkifarea(t_game *game, int *start, int *end);
int		createarea(t_game *game, int start, int end);
void	changevalue(t_game *game);
void	getareainfo(t_game *game, int start, int end);

// mapChecker.c
int		checkextension(char *str, char *extension);

// mapCheckerInput.c
int		checkall(t_game *game);
int		checkotherchar(t_game game);
int		checkwall(t_game game);
int		checkplayer(t_game *game);

// mapColor.c
int		create_rgb(int *tab);
int		getcolor_c(t_game *game);
int		getcolor_f(t_game *game);
int		addvaluecolor(char *line, int *color);
int		*setcolortab(char **color);

// mapCreate.c
int		createmap(t_game *game);
void	putpos(t_game *game, int x, int y);

// mapSize.c
int		calculatemapsize(char *pathmap, t_game *game);

// mapTexture.c
int		getmapinfo(t_game *game);
int		gettexturen(t_game *game);
int		gettexturee(t_game *game);
int		gettextures(t_game *game);
int		gettexturew(t_game *game);

// mapUtils.c
int		addvaluetexture(char *line, char **map_texture);

// init.c
void	initall(t_game *game);
void	inittexture(t_game *game);
void	initvalue(t_game *game);
void	set_fov(t_game *game, double fov_degrees);

// get_next_line.c

char	*get_next_line(int fd);

// utils.c
int		error(char *text);
int		strlenno(char *str);
char	*ft_strdup_size(const char *s, int size);
int		ft_atoiAlpha(const char *nptr);

// utilsfree.c
void	freeend(t_game *game);
int		freeandreturn(char *str);
void	freetab(char **str);
void	freeifnotnull(t_game_map_texture *texture);

// hitbox.c
double	hitbox_x(double pos_x, double move_x, double pos_y, char **map);
double	hitbox_y(double pos_y, double move_y, double pos_x,	char **map);

// key_exec.c
void	head_turn(t_game *game, float angle);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_forward(t_game *game);
void	move_back(t_game *game);

// key_handle.c
int		on_destroy(t_game *game);
int		key_action(t_game *game);
int		on_keypress(int keycode, t_game *game);
int		on_keyrelease(int keycode, t_game *game);

// raycast_utils.c
void	calculate_perp_wall_dist(t_game *game, t_game_ray *rc);
void	calculate_line_height(t_game_ray *rc);
void	hit_point_texture(t_game *game, t_game_ray *rc);
void	init_raycast(t_game *game, t_game_ray *rc, int x);

// raycast.c
void	render_wall(t_game *game, t_game_ray *rc, int x);
void	chosen_side(t_game *game, t_game_ray *rc);
void	dda(t_game *game, t_game_ray *rc);
void	calculate_step(t_game *game, t_game_ray *rc);
void	raycast(t_game *game);

// textures.c
void	draw_ceiling(t_game *game, int x, int draw_start, int draw_end);
void	draw_floor(t_game *game, int x, int draw_start, int draw_end);
void	img_pix_put(t_texture *img, int x, int y, int color);
void	load_wall(t_game *game);

#endif