/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/11 08:55:51 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <math.h>

typedef struct s_game
{
    void *mlx_ptr;
    void *win_ptr;
    float posX, posY;   // Player position
    float dirX, dirY;   // Direction vector
    float planeX, planeY; // Camera plane
} t_game;


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

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
        float rayDirX = game->dirX + game->planeX * cameraX;
        float rayDirY = game->dirY + game->planeY * cameraX;

        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

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
            sideDistX = (game->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
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
            perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        int color = 0xFFFFFF;
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
	if (keycode == 65307)
		on_destroy(game);
	else if (keycode == 97)
	{
		game->posY -= 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == 100)
	{
		game->posY += 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == 115 || keycode == 65364)
	{
		game->posX -= 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == 119 || keycode == 65362)
	{
		game->posX += 0.10;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == 65361)
	{
		game->dirX += 0.25;
		game->dirY -= 0.25;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);
	}
	else if (keycode == 65363)
	{
		game->dirX -= 0.25;
		game->dirY += 0.25;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		raycast(game);	
	}
	return (0);
}

int main() {
    t_game game;

    game.mlx_ptr = mlx_init();
    game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "coucou");
    game.posX = 1.5;
    game.posY = 1.5;
    game.dirX = 1;
    game.dirY = 0;
    game.planeX = 0;
    game.planeY = 0.66;

    mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 03, (1L << 1), &on_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
    mlx_loop(game.mlx_ptr);

    return 0;
}
