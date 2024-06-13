/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/13 12:41:27 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};



void load_textures(t_game *game) 
{
	t_game_texture *texture = &game->texture;

	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, "texture/red-brick-wall.xpm", &texture->width, &texture->height);
	if (!texture->img) {
		fprintf(stderr, "Error loading texture\n");
		exit(EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	my_mlx_pixel_put(t_game_texture *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_line(t_game_texture *img, int x, int drawStart, int drawEnd, int color)
{
	for (int y = drawStart; y < drawEnd; y++) 
		my_mlx_pixel_put(img, x, y, color);
}

void	draw_column_texture(t_game_texture *img, t_game *game, t_game_texture *texture, int texX)
{
	double	increment_y;
	double	tex_y;
	int		color;
	int		pixel_index;

	increment_y = (double)texture->height / game->ray.lineHeight;
	tex_y = (game->ray.start_point.y - WIN_HEIGHT / 2 + game->ray.lineHeight / 2)
		* increment_y;
	if (tex_y < 0)
		tex_y = 0;
	while (game->ray.start_point.y < game->ray.end_point.y)
	{
		pixel_index = (((int)tex_y % texture->height) * texture->line_length)
			+ (texX * (texture->bits_per_pixel / 8));
		color = *(int *)(texture->addr + pixel_index);
		my_mlx_pixel_put(img, game->ray.start_point.x, game->ray.start_point.y, color);
		tex_y += increment_y;
		game->ray.start_point.y++;
	}
}

void raycast(t_game *game) 
{
	for (int x = 0; x < WIN_WIDTH; x++) 
	{
		game->ray.cameraX = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera space
		game->ray.rayDir.x = game->pos.dirX + game->pos.planeX * game->ray.cameraX;
		game->ray.rayDir.y = game->pos.dirY + game->pos.planeY * game->ray.cameraX;

		game->ray.map.x = (int)game->pos.posX;
		game->ray.map.y = (int)game->pos.posY;

		game->ray.deltaDist.x = fabs(1 / game->ray.rayDir.x);
		game->ray.deltaDist.y = fabs(1 / game->ray.rayDir.y);

		int hit = 0;

		if (game->ray.rayDir.x < 0) 
		{
			game->ray.step.x = -1;
			game->ray.sideDist.x = (game->pos.posX - game->ray. map.x) * game->ray.deltaDist.x;
		} 
		else 
		{
			game->ray.step.x = 1;
			game->ray.sideDist.x = (game->ray.map.x + 1.0 - game->pos.posX) * game->ray.deltaDist.x;
		}
		if (game->ray.rayDir.y < 0) 
		{
			game->ray.step.y = -1;
			game->ray.sideDist.y = (game->pos.posY - game->ray.map.y) * game->ray.deltaDist.y;
		} 
		else 
		{
			game->ray.step.y = 1;
			game->ray.sideDist.y = (game->ray.map.y + 1.0 - game->pos.posY) * game->ray.deltaDist.y;
		}

		while (hit == 0) 
		{
			if (game->ray.sideDist.x < game->ray.sideDist.y) 
			{
				game->ray.sideDist.x += game->ray.deltaDist.x;
				game->ray.map.x += game->ray.step.x;
				game->ray.side = 0;
			} 
			else 
			{
				game->ray.sideDist.y += game->ray.deltaDist.y;
				game->ray.map.y += game->ray.step.y;
				game->ray.side = 1;
			}
			if (map[game->ray.map.x][game->ray.map.y] > 0) 
				hit = 1;
		}

		if (game->ray.side == 0)
			game->ray.perpWallDist = (game->ray.map.x - game->pos.posX + (1 - game->ray.step.x) / 2) / game->ray.rayDir.x;
		else
			game->ray.perpWallDist = (game->ray.map.y - game->pos.posY + (1 - game->ray.step.y) / 2) / game->ray.rayDir.y;

		game->ray.lineHeight = (int)(WIN_HEIGHT / game->ray.perpWallDist);

		game->ray.drawStart = -game->ray.lineHeight / 2 + WIN_HEIGHT / 2;
		if (game->ray.drawStart < 0) 
			game->ray.drawStart = 0;
		game->ray.drawEnd = game->ray.lineHeight / 2 + WIN_HEIGHT / 2;
		if (game->ray.drawEnd >= WIN_HEIGHT) 
			game->ray.drawEnd = WIN_HEIGHT - 1;
		int texWidth = game->texture.width;

		float wallX;
		if (game->ray.side == 0) 
			wallX = game->pos.posY + game->ray.perpWallDist * game->ray.rayDir.y;
		else 
			wallX = game->pos.posX + game->ray.perpWallDist * game->ray.rayDir.x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (float)texWidth);
		if (game->ray.side == 0 && game->ray.rayDir.x > 0) 
			texX = texWidth - texX - 1;
		if (game->ray.side == 1 && game->ray.rayDir.y < 0) 
			texX = texWidth - texX - 1;

		game->ray.start_point = (t_coord_int){x, game->ray.drawStart};
		game->ray.end_point = (t_coord_int){x, game->ray.drawEnd};
		draw_column_texture(&game->img, game, &game->texture, texX);
		draw_line(&game->img, x, 0, game->ray.drawStart, 0xFA2FEF);
		draw_line(&game->img, x, game->ray.drawEnd, WIN_HEIGHT, 0x0AC03F);
	}
}

int main_loop(t_game *game) 
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
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
	float oldDirX = game->pos.dirX;
	game->pos.dirX = game->pos.dirX * cos(angle) - game->pos.dirY * sin(angle);
	game->pos.dirY = oldDirX * sin(angle) + game->pos.dirY * cos(angle);

	float oldPlaneX = game->pos.planeX;
	game->pos.planeX = game->pos.planeX * cos(angle) - game->pos.planeY * sin(angle);
	game->pos.planeY = oldPlaneX * sin(angle) + game->pos.planeY * cos(angle);
	// printf("dirY = %f || dirX = %f\n", game->dirY, game->dirX);
	// printf("planeY = %f || planeX = %f\n", game->planeY, game->planeX);
}

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		on_destroy(game);
	else if (keycode == 97)
	{
		game->pos.posX -= game->pos.planeX * 0.10;
		game->pos.posY -= game->pos.planeY * 0.10;
	}
	else if (keycode == 100)
	{
		game->pos.posX += game->pos.planeX * 0.10;
		game->pos.posY += game->pos.planeY * 0.10;
	}
	else if (keycode == 115 || keycode == 65364)
	{
		game->pos.posX -= game->pos.dirX * 0.10;
		game->pos.posY -= game->pos.dirY * 0.10;
	}
	else if (keycode == 119 || keycode == 65362)
	{
		game->pos.posX += game->pos.dirX * 0.10;
		game->pos.posY += game->pos.dirY * 0.10;
	}
	else if (keycode == 65361)
	{
		head_turn(game, -0.10);
	}
	else if (keycode == 65363)
	{
		head_turn(game, 0.10);

	}
	printf("posY = %f || posX = %f\n", game->pos.posY, game->pos.posX);
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
		game.mesure.line = calculateMapSize(argv[1], &game.mesure.column);
		if (checkSize(game))
			return (1);
		inputArea(argv[1], &game);
		if (checkAll(&game))
			return (freeTab(&game), 0);
	}
	/*int fd = open("maps/good/5*5.cub", O_RDONLY);
	printf("%s", get_next_line(fd));*/
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Je t'aime Mathieu");
	game.pos.posX = 1.5;
	game.pos.posY = 1.5;
	game.pos.dirX = 1; // 1 south // -1 north
	game.pos.dirY = 0; // -1 west // 1 east
	game.pos.planeX = 0; // 0.66 west // -0.66 easy 
	game.pos.planeY = 0.66; // 0.66 south // -0.66 north
	load_textures(&game);
	game.img.img = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);

	mlx_loop_hook(game.mlx_ptr, main_loop, &game);
	mlx_hook(game.win_ptr, 02, (1L << 0), &on_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), &on_destroy, &game);
	mlx_loop(game.mlx_ptr);

	return 0;
}
