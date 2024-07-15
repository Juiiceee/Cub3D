/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 15:11:34 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void img_pix_put(t_texture *img, int x, int y, int color)
{
	char *pixel;
	int i;

	i = img->bpp - 8;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void load_wall(t_game *game)
{
	t_texture *north = &game->textures.north;
	t_texture *east = &game->textures.east;
	t_texture *west = &game->textures.west;
	t_texture *south = &game->textures.south;

	north->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.north, &north->width, &north->height);
	south->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.south, &south->width, &south->height);
	east->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.east, &east->width, &east->height);
	west->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.west, &west->width, &west->height);
	if (!north->img || !south->img || !west->img || !east->img)
		return;
	north->data = mlx_get_data_addr(north->img, &north->bpp, &north->size_line, &north->endian);
	south->data = mlx_get_data_addr(south->img, &south->bpp, &south->size_line, &south->endian);
	east->data = mlx_get_data_addr(east->img, &east->bpp, &east->size_line, &east->endian);
	west->data = mlx_get_data_addr(west->img, &west->bpp, &west->size_line, &west->endian);
}

void draw_line(t_game *game, int x, int drawStart, int drawEnd, int color)
{
	for (int y = drawStart; y < drawEnd; y++)
	{
		img_pix_put(&game->img, x, y, color);
	}
}

void init_raycast(t_game *game, t_game_ray *rc, int x)
{
	rc->cameraX = 2 * x / (float)WIN_WIDTH - 1;
	rc->rayDir.x = game->pos.dirx + game->pos.planex * rc->cameraX;
	rc->rayDir.y = game->pos.diry + game->pos.planey * rc->cameraX;
	rc->map.x = (int)game->pos.posx;
	rc->map.y = (int)game->pos.posy;
	rc->deltaDist.x = fabs(1 / rc->rayDir.x);
	rc->deltaDist.y = fabs(1 / rc->rayDir.y);
}

void calculate_step(t_game *game, t_game_ray *rc)
{
	if (rc->rayDir.x < 0)
	{
		rc->step.x = -1;
		rc->sideDist.x = (game->pos.posx - rc->map.x) * rc->deltaDist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->sideDist.x = (rc->map.x + 1.0 - game->pos.posx) * rc->deltaDist.x;
	}
	if (rc->rayDir.y < 0)
	{
		rc->step.y = -1;
		rc->sideDist.y = (game->pos.posy - rc->map.y) * rc->deltaDist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->sideDist.y = (rc->map.y + 1.0 - game->pos.posy) * rc->deltaDist.y;
	}
}

void chosen_side(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0) 
	{
		if (rc->rayDir.x > 0)
        rc->sprite = game->textures.west;
		else 
		rc->sprite = game->textures.east;
    } 
	else 
	{
		if (rc->rayDir.y > 0)
        rc->sprite = game->textures.north;
		else 
		rc->sprite = game->textures.south;
    }
}

void dda(t_game *game, t_game_ray *rc)
{
	rc->hit = 0;

	while (rc->hit == 0)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->map.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->map.y += rc->step.y;
			rc->side = 1;
		}
		if (game->area[rc->map.y][rc->map.x] != '0')
		{
			rc->hit = 1;
			chosen_side(game, rc);
		}
	}
}

void calculate_perp_wall_dist(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
		rc->perpWallDist =
			(rc->map.x - game->pos.posx + (1 - rc->step.x) / 2) / rc->rayDir.x;
	else
		rc->perpWallDist =
			(rc->map.y - game->pos.posy + (1 - rc->step.y) / 2) / rc->rayDir.y;
}

void calculate_line_height(t_game_ray *rc)
{
	rc->lineHeight = (int)(WIN_HEIGHT / rc->perpWallDist);
	rc->drawStart = -rc->lineHeight / 2 + WIN_HEIGHT / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + WIN_HEIGHT / 2;
	if (rc->drawEnd >= WIN_HEIGHT)
		rc->drawEnd = WIN_HEIGHT - 1;
}

void hit_point_texture(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
		rc->wallX = game->pos.posy + rc->perpWallDist * rc->rayDir.y;
	else
		rc->wallX = game->pos.posx + rc->perpWallDist * rc->rayDir.x;
	rc->wallX -= floor(rc->wallX);
	rc->texWidth = rc->sprite.width;
	rc->texX = (int)(rc->wallX * (float)rc->texWidth);
	if (rc->side == 0 && rc->rayDir.x > 0)
		rc->texX = rc->texWidth - rc->texX - 1;
	if (rc->side == 1 && rc->rayDir.y < 0)
		rc->texX = rc->texWidth - rc->texX - 1;
}

void render_wall(t_game *game, t_game_ray *rc, int x)
{
	int y = rc->drawStart;
	
	while (y <= rc->drawEnd)
    {
        int d = y * 256 - WIN_HEIGHT * 128 + rc->lineHeight * 128;
        int texY = ((d * rc->sprite.height) / rc->lineHeight) / 256;
        char *pixel = rc->sprite.data + (texY *rc->sprite.size_line 
                      + rc->texX * (rc->sprite.bpp / 8));
        img_pix_put(&game->img, x, y, *(int *)pixel);
		y++;
    }
}

void raycast(t_game *game)
{
	int x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		t_game_ray raycast;		

		init_raycast(game, &raycast, x);
		calculate_step(game, &raycast);
		dda(game, &raycast);
		calculate_perp_wall_dist(game, &raycast);
		calculate_line_height(&raycast);
		hit_point_texture(game, &raycast);
		render_wall(game, &raycast, x);
		draw_line(game, x, 0, raycast.drawStart, game->map_info.color_ceiling);
		if (raycast.drawEnd != WIN_HEIGHT - 1)
			draw_line(game, x, raycast.drawEnd, WIN_HEIGHT, game->map_info.color_floor);
		x++;
	}
}

int on_destroy(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img.img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	freeend(game);
	exit(0);
}

void head_turn(t_game *game, float angle)
{
	float oldDirX = game->pos.dirx;
	game->pos.dirx = game->pos.dirx * cos(angle) - game->pos.diry * sin(angle);
	game->pos.diry = oldDirX * sin(angle) + game->pos.diry * cos(angle);

	float oldPlaneX = game->pos.planex;
	game->pos.planex = game->pos.planex * cos(angle) - game->pos.planey * sin(angle);
	game->pos.planey = oldPlaneX * sin(angle) + game->pos.planey * cos(angle);
}

double	update_pos_x(double pos_x, double move_x, double pos_y, char **map)
{
	int		y_out;
	int		y_in;
	int		future_x;

	y_in = (int)(pos_y + 0.1);
	y_out = (int)(pos_y - 0.1);
	if (move_x < 0)
		future_x = (int)(pos_x + move_x - 0.1);
	else
		future_x = (int)(pos_x + move_x + 0.1);
	if (map[y_in][future_x] != '1'
		&& map[y_out][future_x] != '1')
		pos_x += move_x;
	return (pos_x);
}

double	update_pos_y(double pos_y, double move_y, double pos_x,	char **map)
{
	int		x_out;
	int		x_in;
	int		future_y;

	x_in = (int)(pos_x + 0.1);
	x_out = (int)(pos_x - 0.1);
	if (move_y < 0)
		future_y = (int)(pos_y + move_y - 0.1);
	else
		future_y = (int)(pos_y + move_y + 0.1);
	if (map[future_y][x_in] != '1'
		&& map[future_y][x_out] != '1')
		pos_y += move_y;
	return (pos_y);
}

void move_left(t_game *game)
{
    double move_x = -game->pos.planex * 0.10;
    double move_y = -game->pos.planey * 0.10;

    game->pos.posx = update_pos_x(game->pos.posx, move_x, game->pos.posy, game->area);
    game->pos.posy = update_pos_y(game->pos.posy, move_y, game->pos.posx, game->area);
}

void move_right(t_game *game)
{
    double move_x = game->pos.planex * 0.10;
    double move_y = game->pos.planey * 0.10;

    game->pos.posx = update_pos_x(game->pos.posx, move_x, game->pos.posy, game->area);
    game->pos.posy = update_pos_y(game->pos.posy, move_y, game->pos.posx, game->area);
}

void move_forward(t_game *game)
{
    double move_x = game->pos.dirx * 0.10;
    double move_y = game->pos.diry * 0.10;

    game->pos.posx = update_pos_x(game->pos.posx, move_x, game->pos.posy, game->area);
    game->pos.posy = update_pos_y(game->pos.posy, move_y, game->pos.posx, game->area);
}

void move_back(t_game *game)
{
    double move_x = -game->pos.dirx * 0.10;
    double move_y = -game->pos.diry * 0.10;

    game->pos.posx = update_pos_x(game->pos.posx, move_x, game->pos.posy, game->area);
    game->pos.posy = update_pos_y(game->pos.posy, move_y, game->pos.posx, game->area);
}

int key_action(t_game *game)
{
	if (game->key[ESCAPE])
		on_destroy(game);
	if (game->key[A_KEY])
		move_left(game);
	if (game->key[D_KEY])
		move_right(game);
	if (game->key[S_KEY])
		move_back(game);
	if (game->key[W_KEY])
		move_forward(game);
	if (game->key[Larrow_KEY])
		head_turn(game, 0.10);
	if (game->key[Rarrow_KEY])
		head_turn(game, -0.10);
	return (0);
}

int on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		game->key[ESCAPE] = 1;
	else if (keycode == XK_a)
		game->key[A_KEY] = 1;
	else if (keycode == XK_d)
		game->key[D_KEY] = 1;
	else if (keycode == XK_s || keycode == XK_Down)
		game->key[S_KEY] = 1;
	else if (keycode == XK_w || keycode == XK_Up)
		game->key[W_KEY] = 1;
	else if (keycode == XK_Left)
		game->key[Larrow_KEY] = 1;
	else if (keycode == XK_Right)
		game->key[Rarrow_KEY] = 1;
	return (0);
}

int on_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		game->key[ESCAPE] = 0;
	else if (keycode == XK_a)
		game->key[A_KEY] = 0;
	else if (keycode == XK_d)
		game->key[D_KEY] = 0;
	else if (keycode == XK_s || keycode == XK_Down)
		game->key[S_KEY] = 0;
	else if (keycode == XK_w || keycode == XK_Up)
		game->key[W_KEY] = 0;
	else if (keycode == XK_Left)
		game->key[Larrow_KEY] = 0;
	else if (keycode == XK_Right)
		game->key[Rarrow_KEY] = 0;
	return (0);
}

void set_fov(t_game *game, double fov_degrees)
{
	double fov_radians = (fov_degrees)*M_PI / 180.0;
	double half_fov_tan = tan(fov_radians / 2.0);

	game->pos.planex = game->pos.diry * half_fov_tan;
	game->pos.planey = -game->pos.dirx * half_fov_tan;
}

int main_loop(t_game *game)
{
	raycast(game);
	key_action(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	t_game game;
	if (argc == 2)
	{
		initall(&game);
		if (checkextension(argv[1], ".cub"))
			return (1);
		if (calculatemapsize(argv[1], &game))
			return (1);
		if (getmapinfo(&game))
			return (freetab(game.map), freeifnotnull(&game.map_info.map_texture), free(game.map_info.pathmap), 1);
		if (checkall(&game))
			return (freeend(&game), 1);
		int i = 0;
		while (game.area[i])
			printf("%s\n", game.area[i++]);
	}
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Je t'aime wikow <3");
	game.pos.dirx = 0;
	game.pos.diry = 1;
	set_fov(&game, 90);

	load_wall(&game);
	game.img.img = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);

	game.img.data = mlx_get_data_addr(game.img.img, &game.img.bpp,
									  &game.img.size_line, &game.img.endian);

	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 02, (1L << 0), &on_keypress, &game);
	mlx_hook(game.win_ptr, 03, (1L << 1), &on_keyrelease, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
	mlx_loop(game.mlx_ptr);
	freeend(&game);
	return 0;
}
