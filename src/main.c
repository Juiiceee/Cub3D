/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/19 16:11:23 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

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


void draw_line(t_game *game, int x, int drawStart, int drawEnd, int color) {
	for (int y = drawStart; y < drawEnd; y++) {
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
	}
}

void raycast(t_game *game) 
{
	for (int x = 0; x < WIN_WIDTH; x++) 
	{
		float cameraX = 2 * x / (float)WIN_WIDTH - 1; // x-coordinate in camera space
		float rayDirX = game->pos.dirx + game->pos.planex * cameraX;
		float rayDirY = game->pos.diry + game->pos.planey * cameraX;

		int mapX = (int)game->pos.posx;
		int mapY = (int)game->pos.posy;

		float sideDistX;
		float sideDistY;

		float deltaDistX = fabs(1 / rayDirX);
		float deltaDistY = fabs(1 / rayDirY);
		float perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; 
		int side;

		if (rayDirX < 0) 
		{
			stepX = -1;
			sideDistX = (game->pos.posx - mapX) * deltaDistX;
		} 
		else 
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->pos.posx) * deltaDistX;
		}
		if (rayDirY < 0) 
		{
			stepY = -1;
			sideDistY = (game->pos.posy - mapY) * deltaDistY;
		} 
		else 
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->pos.posy) * deltaDistY;
		}

		while (hit == 0) 
		{
			if (sideDistX < sideDistY) 
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} 
			else 
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map[mapX][mapY] > 0) 
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - game->pos.posx + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->pos.posy + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0) 
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;

		if (drawEnd >= WIN_HEIGHT) 
			drawEnd = WIN_HEIGHT - 1;

		int color = 0xFFFFFF;
			if (side == 1) color = color / 2;
		draw_line(game, x, 0, drawStart, 0xFA2FEF);
		draw_line(game, x, drawStart, drawEnd, color);
		draw_line(game, x, drawEnd, WIN_HEIGHT, 0x0AC03F);
	}
}

int main_loop(t_game *game) {
	raycast(game);
	return 0;
}

int	on_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
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
	// printf("dirY = %f || dirX = %f\n", game->dirY, game->dirX);
	// printf("planeY = %f || planeX = %f\n", game->planeY, game->planeX);
}

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		on_destroy(game);
	else if (keycode == XK_a)
	{
		game->pos.posx -= game->pos.planex * 0.10;
		game->pos.posy -= game->pos.planey * 0.10;
	}
	else if (keycode == XK_d)
	{
		game->pos.posx += game->pos.planex * 0.10;
		game->pos.posy += game->pos.planey * 0.10;
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		game->pos.posx -= game->pos.dirx * 0.10;
		game->pos.posy -= game->pos.diry * 0.10;
	}
	else if (keycode == XK_w || keycode == XK_Up)
	{
		game->pos.posx += game->pos.dirx * 0.10;
		game->pos.posy += game->pos.diry * 0.10;
	}
	else if (keycode == XK_Left)
	{
		head_turn(game, -0.10);
	}
	else if (keycode == XK_Right)
	{
		head_turn(game, 0.10);

	}
	printf("posY = %f || posX = %f\n", game->pos.posy, game->pos.posx);
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;
	/*char *argv[] = {"caca", "maps/good/5*5.cub", 0};
	int argc = 2;*/

	if (argc == 2)
	{
		if (checkExtension(argv[1]))
			return (1);
		calculateMapSize(argv[1], &game.mesure.column);
		if (checkSize(game))
			return (1);
		inputArea(argv[1], &game);
		if (checkAll(&game))
			return (freetab(&game), 0);
	}
	/*int fd = open("maps/good/5*5.cub", O_RDONLY);
	printf("%s", get_next_line(fd));*/
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Je t'aime Mathieu");
	game.pos.posx = 1.5;
	game.pos.posy = 1.5;
	game.pos.dirx = 1; // 1 south // -1 north
	game.pos.diry = 0; // -1 west // 1 east
	game.pos.planex = 0; // 0.66 west // -0.66 easy 
	game.pos.planey = 0.66; // 0.66 south // -0.66 north

	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 02, (1L << 0), &on_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
	mlx_loop(game.mlx_ptr);

	return 0;
}
