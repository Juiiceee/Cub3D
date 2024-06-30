/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/01 00:29:41 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void img_pix_put(t_game_texture *img, int x, int y, int color)
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

int map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void load_wall(t_game *game)
{
	t_game_texture *texture = &game->texture;

	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, "texture/red-brick-wall.xpm", &texture->width, &texture->height);
	if (!texture->img)
	{
		fprintf(stderr, "Error loading texture\n");
		exit(EXIT_FAILURE);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
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
    rc->rayDir.x = game->pos.dirX + game->pos.planeX * rc->cameraX;
    rc->rayDir.y = game->pos.dirY + game->pos.planeY * rc->cameraX;
    rc->map.x = (int)game->pos.posX;
    rc->map.y = (int)game->pos.posY;
    rc->deltaDist.x = fabs(1 / rc->rayDir.x);
    rc->deltaDist.y = fabs(1 / rc->rayDir.y);
}

void calculate_step(t_game *game, t_game_ray* rc)
{
    if (rc->rayDir.x < 0)
    {
        rc->step.x = -1;
        rc->sideDist.x = (game->pos.posX - rc->map.x) * rc->deltaDist.x;
    }
    else
    {
        rc->step.x = 1;
        rc->sideDist.x = (rc->map.x + 1.0 - game->pos.posX) * rc->deltaDist.x;
    }
    if (rc->rayDir.y < 0)
    {
        rc->step.y = -1;
        rc->sideDist.y = (game->pos.posY - rc->map.y) * rc->deltaDist.y;
    }
    else
    {
        rc->step.y = 1;
        rc->sideDist.y = (rc->map.y + 1.0 - game->pos.posY) * rc->deltaDist.y;
    }
}

void dda(t_game_ray *rc)
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
        if (map[rc->map.x][rc->map.y] > 0)
            rc->hit = 1;
    }
}

void calculate_perp_wall_dist(t_game *game, t_game_ray *rc)
{
    if (rc->side == 0)
        rc->perpWallDist = 
		(rc->map.x - game->pos.posX + (1 - rc->step.x) / 2) / rc->rayDir.x;
    else
        rc->perpWallDist = 
		(rc->map.y - game->pos.posY + (1 - rc->step.y) / 2) / rc->rayDir.y;
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
        rc->wallX = game->pos.posY + rc->perpWallDist * rc->rayDir.y;
    else
        rc->wallX = game->pos.posX + rc->perpWallDist * rc->rayDir.x;
    rc->wallX -= floor(rc->wallX);
    rc->texWidth = game->texture.width;
	rc->texX = (int)(rc->wallX * (float)rc->texWidth);
    if (rc->side == 0 && rc->rayDir.x > 0)
        rc->texX = rc->texWidth - rc->texX - 1;
    if (rc->side == 1 && rc->rayDir.y < 0)
        rc->texX = rc->texWidth - rc->texX - 1;

}

void render_wall(t_game *game, t_game_ray *rc, int x)
{
	int y = rc->drawStart;
	
	while (y < rc->drawEnd)
    {
        int d = y * 256 - WIN_HEIGHT * 128 + rc->lineHeight * 128;
        int texY = ((d * game->texture.height) / rc->lineHeight) / 256;
        char *pixel = game->texture.data + (texY * game->texture.size_line 
                      + rc->texX * (game->texture.bpp / 8));
        int color = *(int *)pixel;
        if (rc->side == 1)
            color = (color >> 1) & 8355711;
        img_pix_put(&game->img, x, y, color);
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
        dda(&raycast);
        calculate_perp_wall_dist(game, &raycast);
        calculate_line_height(&raycast);
        hit_point_texture(game, &raycast);
		render_wall(game, &raycast, x);
		draw_line(game, x, 0, raycast.drawStart, 0xFA2FEF);
		draw_line(game, x, raycast.drawEnd, WIN_HEIGHT, 0x0AC03F);
    	x++;
	}
}

int main_loop(t_game *game)
{
	raycast(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	return 0;
}

int on_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(0);
}

void head_turn(t_game *game, float angle)
{
	float oldDirX = game->pos.dirX;
	game->pos.dirX = game->pos.dirX * cos(angle) - game->pos.dirY * sin(angle);
	game->pos.dirY = oldDirX * sin(angle) + game->pos.dirY * cos(angle);

	float oldPlaneX = game->pos.planeX;
	game->pos.planeX = game->pos.planeX * cos(angle) - game->pos.planeY * sin(angle);
	game->pos.planeY = oldPlaneX * sin(angle) + game->pos.planeY * cos(angle);
	// printf("dirY = %f || dirX = %f\n", game->dirY, game->dirX);
	// printf("planeY = %f || planeX = %f\n", game->planeY, game->planeX);
}

int on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		on_destroy(game);
	else if (keycode == XK_a)
	{
		game->pos.posX -= game->pos.planeX * 0.10;
		game->pos.posY -= game->pos.planeY * 0.10;
	}
	else if (keycode == XK_d)
	{
		game->pos.posX += game->pos.planeX * 0.10;
		game->pos.posY += game->pos.planeY * 0.10;
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		game->pos.posX -= game->pos.dirX * 0.10;
		game->pos.posY -= game->pos.dirY * 0.10;
	}
	else if (keycode == XK_w || keycode == XK_Up)
	{
		game->pos.posX += game->pos.dirX * 0.10;
		game->pos.posY += game->pos.dirY * 0.10;
	}
	else if (keycode == XK_Left)
	{
		head_turn(game, 0.10);
	}
	else if (keycode == XK_Right)
	{
		head_turn(game, -0.10);
	}
	return (0);
}

void set_fov(t_game *game, double fov_degrees)
{
    double fov_radians = (fov_degrees) * M_PI / 180.0;
    double half_fov_tan = tan(fov_radians / 2.0);

    game->pos.planeX = game->pos.dirY * half_fov_tan;
    game->pos.planeY = -game->pos.dirX * half_fov_tan;
}

int main(int argc, char **argv)
{
	t_game game;
	(void) argc;
	(void) argv;
	/*char *argv[] = {"caca", "maps/good/5*5.cub", 0};
	int argc = 2;*/

	// if (argc == 2)
	// {
	// 	if (checkExtension(argv[1]))
	// 		return (1);
	// 	game.mesure.line = calculawallpaperteMapSize(argv[1], &game.mesure.column);
	// 	if (checkSize(game))
	// 		return (1);
	// 	inputArea(argv[1], &game);
	// 	if (checkAll(&game))
	// 		return (freeTab(&game), 0);
	// }
	/*int fd = open("maps/good/5*5.cub", O_RDONLY);
	printf("%s", get_next_line(fd));*/
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Je t'aime wikow <3");
    game.pos.posX = 1.5;
    game.pos.posY = 1.5;
	game.pos.dirX = 0;
    game.pos.dirY = 1;
 	set_fov(&game, 70);

	load_wall(&game);
	game.img.img = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	
	game.img.data = mlx_get_data_addr(game.img.img, &game.img.bpp,
			&game.img.size_line, &game.img.endian);


	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 02, (1L << 0), &on_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
	mlx_loop(game.mlx_ptr);

	return 0;
}
