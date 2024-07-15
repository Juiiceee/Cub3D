/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 17:49:42 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	set_fov(&game, 110);

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
