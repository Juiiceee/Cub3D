/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/30 13:34:05 by lbehr            ###   ########.fr       */
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
			return (1);
		int i = 0;
		while (game.area[i])
			printf("%s\n", game.area[i++]);
		freeend(&game);
	}
	return 0;
}
