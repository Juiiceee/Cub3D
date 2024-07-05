/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/04 17:50:39 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int main(/*int argc, char **argv*/)
{
	t_game game;
	char *argv[] = {"caca", "oui.cub", 0};

	/*if (argc == 2)
	{*/
		ft_bzero(&game, sizeof(t_game));
		if (checkextension(argv[1], ".cub"))
			return (1);
		if (calculatemapsize(argv[1], &game))
			return (1);
		if (getmapinfo(&game))
			return (1);
		if (checkall(&game))
			return (1);
		int p = 0;
		while (game.area[p])
			printf("%s\n", game.area[p++]);
		freeend(&game);
	//}
	return 0;
}
