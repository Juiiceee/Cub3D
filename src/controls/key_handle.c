/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:34 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/16 13:12:27 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	on_destroy(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img.img);
	mlx_destroy_image(game->mlx_ptr, game->textures.north.img);
	mlx_destroy_image(game->mlx_ptr, game->textures.east.img);
	mlx_destroy_image(game->mlx_ptr, game->textures.west.img);
	mlx_destroy_image(game->mlx_ptr, game->textures.south.img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	freeend(game);
	exit(0);
}

int	key_action(t_game *game)
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
		head_turn(game, 0.005);
	if (game->key[Rarrow_KEY])
		head_turn(game, -0.005);
	return (0);
}

int	on_keypress(int keycode, t_game *game)
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

int	on_keyrelease(int keycode, t_game *game)
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
