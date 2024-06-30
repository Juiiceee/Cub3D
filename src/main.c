/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/06/30 12:11:03 by lbehr            ###   ########.fr       */
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
		inittexture(&game);
		if (checkExtension(argv[1], ".cub"))
			return (1);
		if (calculateMapSize(argv[1], &game))
			return (1);
		if (recomapinfo(&game))
			return (1);
		int i = 0;
		while (game.area[i])
			printf("%s\n", game.area[i++]);
		freeend(&game);
	}
	return 0;
}
