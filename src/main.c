/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/03 14:00:05 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int main(/*int argc, char **argv*/)
{
	t_game game;
	char *argv[] = {"caca", "oui.cub", 0};
	int argc = 2;

	if (argc == 2)
	{
		initall(&game);
		if (checkextension(argv[1], ".cub"))
			return (1);
		if (calculatemapsize(argv[1], &game))
			return (1);
		if (getmapinfo(&game))
			return (freetab(game.map), freeifnotnull(&game.map_info.map_texture),free(game.map_info.pathmap), 1);
		if (checkall(&game))
			return (freeend(&game), 1);
		int p = 0;
		while (game.area[p])
			printf("%s\n", game.area[p++]);
		freeend(&game);
	}
	return 0;
}
