/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/11 15:50:43 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

// int main(int argc, char *argv[])
// {
// 	t_data	data;
	
// 	(void) argv;
// 	if (argc != 2)
// 	{
// 		exit(1);
// 	}
// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "hi :)");
// 	if (!data.win_ptr)
// 		return (free(data.mlx_ptr), 1);
// 	mlx_hook(data.win_ptr, 03, (1L << 1), &on_keypress, &data);
// 	mlx_hook(data.win_ptr, 17, (1L << 17), &on_destroy, &data);
// 	mlx_loop(data.mlx_ptr);
// }

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

void raycast(t_game *game) {
	for (int x = 0; x < WIN_WIDTH; x++) {
		float cameraX = 2 * x / (float)WIN_WIDTH - 1; // x-coordinate in camera space
		float rayDirX = game->dirx + game->planex * cameraX;
		float rayDirY = game->diry + game->planey * cameraX;

		int mapX = (int)game->posx;
		int mapY = (int)game->posy;

		float sideDistX;
		float sideDistY;

		float deltaDistX = fabs(1 / rayDirX);
		float deltaDistY = fabs(1 / rayDirY);
		float perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; 
		int side;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (game->posx - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->posx) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (game->posy - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->posy) * deltaDistY;
		}

		while (hit == 0) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map[mapX][mapY] > 0) hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - game->posx + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->posy + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

		int color = WHITE;
		if (side == 1) color = color / 2;

		draw_line(game, x, drawStart, drawEnd, color);
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

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		on_destroy(game);
	else if (keycode == XK_a)
	{
		game->posy -= 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == XK_d)
	{
		game->posy += 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		game->posx -= 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == XK_w || keycode == XK_Up)
	{
		game->posx += 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == XK_Left)
	{
		game->dirx += 0.25;
		game->diry -= 0.25;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == XK_Right)
	{
		game->dirx -= 0.25;
		game->diry += 0.25;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);	
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;

	if (argc == 2)
	{
		if (!checkExtension(argv[1]))
			return (0);
		game.mesure.line = calculateMapSize(argv[1], &game.mesure.column);
		if (!checkSize(game))
			return (0);
		inputArea(argv[1], &game);
		if (!checkall(&game))
			return (freetab(&game), 0);
	}
	/*game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Je t'aime Mathieu");
	game.posx = 1.5;
	game.posy = 1.5;
	game.dirx = 1;
	game.diry = 0;
	game.planex = 0;
	game.planey = 0.66;

	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 03, (1L << 1), &on_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
	mlx_loop(game.mlx_ptr);

	return 0;*/
}
