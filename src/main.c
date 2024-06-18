/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/18 15:38:24 by mda-cunh         ###   ########.fr       */
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
void load_ceilling(t_game *game)
{
	t_game_texture *texture = &game->ceiling_texture;

	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, "texture/floor.xpm", &texture->width, &texture->height);
	if (!texture->img)
	{
		fprintf(stderr, "Error loading texture\n");
		exit(EXIT_FAILURE);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}
void load_floor(t_game *game)
{
	t_game_texture *texture = &game->floor_texture;

	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, "texture/ceiling.xpm", &texture->width, &texture->height);
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

void draw_floor_and_ceiling(t_game *game)
{
    for (int y = 0; y < WIN_HEIGHT; y++)
    {
        float rayDirX0 = game->pos.dirX - game->pos.planeX;
        float rayDirY0 = game->pos.dirY - game->pos.planeY;
        float rayDirX1 = game->pos.dirX + game->pos.planeX;
        float rayDirY1 = game->pos.dirY + game->pos.planeY;

        int p = y - WIN_HEIGHT / 2;

        float posZ = 0.5 * WIN_HEIGHT;

        float rowDistance = posZ / p;

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIN_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIN_WIDTH;

        float floorX = game->pos.posX + rowDistance * rayDirX0;
        float floorY = game->pos.posY + rowDistance * rayDirY0;

        for (int x = 0; x < WIN_WIDTH; ++x)
        {
            int cellX = (int)floorX;
            int cellY = (int)floorY;

            int tx = (int)(game->floor_texture.width * (floorX - cellX)) & (game->floor_texture.width - 1);
            int ty = (int)(game->floor_texture.height * (floorY - cellY)) & (game->floor_texture.height - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            int floorColor = *(int *)(game->floor_texture.data + (ty * game->floor_texture.size_line + tx * (game->floor_texture.bpp / 8)));
            int ceilingColor = *(int *)(game->ceiling_texture.data + (ty * game->ceiling_texture.size_line + tx * (game->ceiling_texture.bpp / 8)));

            img_pix_put(&game->img, x, y, floorColor);
            img_pix_put(&game->img, x, WIN_HEIGHT - y - 1, ceilingColor);
        }
    }
}

void raycast(t_game *game)
{
	draw_floor_and_ceiling(game);
	
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		float cameraX = 2 * x / (float)WIN_WIDTH - 1;
		float rayDirX = game->pos.dirX + game->pos.planeX * cameraX;
		float rayDirY = game->pos.dirY + game->pos.planeY * cameraX;

		int mapX = (int)game->pos.posX;
		int mapY = (int)game->pos.posY;

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
			sideDistX = (game->pos.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->pos.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->pos.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->pos.posY) * deltaDistY;
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
			perpWallDist = (mapX - game->pos.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->pos.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;

		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int color = 0xFFFFFF;
		if (side == 1)
			color = color / 2;

		int texWidth = game->texture.width;

		float wallX;
		if (side == 0)
			wallX = game->pos.posY + perpWallDist * rayDirY;
		else
			wallX = game->pos.posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (float)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		for (int y = drawStart; y < drawEnd; y++)
		{
            int d = y * 256 - WIN_HEIGHT * 128 + lineHeight * 128;
            int texY = ((d * game->texture.height) / lineHeight) / 256;
            char *pixel = game->texture.data + (texY * game->texture.size_line + texX * (game->texture.bpp / 8));
            int color = *(int *)pixel;
            if (side == 1)
                color = (color >> 1) & 8355711; // Make y sides darker
            img_pix_put(&game->img, x, y, color);
		}
		// draw_line(game, x, 0, drawStart, 0xFA2FEF);
		// draw_line(game, x, drawEnd, WIN_HEIGHT, 0x0AC03F);
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
		head_turn(game, -0.10);
	}
	else if (keycode == XK_Right)
	{
		head_turn(game, 0.10);
	}
	printf("posY = %f || posX = %f\n", game->pos.posY, game->pos.posX);
	return (0);
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
	game.pos.dirX = 1;		// 1 south // -1 north
	game.pos.dirY = 0;		// -1 west // 1 east
	game.pos.planeX = 0;	// 0.66 west // -0.66 easy
	game.pos.planeY = 0.66; // 0.66 south // -0.66 north

	load_wall(&game);
	load_floor(&game);
	load_ceilling(&game);

	game.img.img = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	
	game.img.data = mlx_get_data_addr(game.img.img, &game.img.bpp,
			&game.img.size_line, &game.img.endian);


	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 02, (1L << 0), &on_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
	mlx_loop(game.mlx_ptr);

	return 0;
}
