/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 15:51:10 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <math.h>
# include "../libft/libft.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define WHITE 0xFFFFFF
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef enum e_bool
{
	False,
	True
}	t_bool;

typedef struct s_game_mesure
{
	int	line;
	int	column;
}	t_game_mesure;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**area;
	t_game_mesure	mesure;
	float			posx;
	float			posy;
	float			dirx;
	float			diry;
	float			planex;
	float			planey;
}	t_game;

// maputils.c

/**
 * Displays an error message and return 1.
 *
 * @param text The error message to display.
 * @return Return 1.
 */
int	error(char *text);
/**
 * Calculates the length of a string excluding the null terminator.
 *
 * @param str The input string.
 * @return The length of the string.
 */
int	strlenno(char *str);
/**
 * Frees the memory allocated for a string and returns a value.
 *
 * @param str The string to be freed.
 * @return Return 0 if the size isn't good.
 */
int	freeAndReturn(char *str);

//mapchecker.c

/**
 * Checks the extension of a given string.
 *
 * This function takes a string as input and checks if it has a valid extension.
 * It returns an integer value indicating whether the extension is valid or not.
 *
 * @param str The string to check the extension of.
 * @return An integer value indicating the validity of the extension.
 */
int	checkExtension(char *str);
/**
 * Checks the size of the game.
 *
 * This function takes a `t_game` object as a parameter and checks the size of the game.
 *
 * @param game The `t_game` object representing the game.
 * @return An integer value indicating the result of the size check.
 */
int	checkSize(t_game game);

// get_next_line.c

/**
 * Reads a line from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return A pointer to the line read from the file descriptor, or NULL if there are no more lines to read or an error occurs.
 */
char	*get_next_line(int fd);

// mapsize.c

/**
 * Calculates the size of the representation of the map.
 *
 * This function takes a map and an integer array as parameters.
 * It calculates the size of the representation of the map and stores it in the `colonne` array.
 *
 * @param map The map to calculate the size of.
 * @param colonne An integer array to store the size of the representation.
 * @return The size of the representation of the map.
 */
int	calculateMapSize(char *map, int *colonne);

//mapcreate.c

/**
 * @brief Reads the input map and initializes the game area.
 * 
 * This function takes a pointer to the input map and a pointer to the game structure.
 * It reads the input map and initializes the game area accordingly.
 * 
 * @param map Pointer to the input map.
 * @param game Pointer to the game structure.
 */
void	inputArea(char *map, t_game *game);

/**
 * @brief Creates a 2D array representing the game area.
 * 
 * This function takes the number of rows and columns as input and returns a 2D array
 * representing the game area. Each element of the array is initially set to NULL.
 * 
 * @param ligne Number of rows in the game area.
 * @param colonne Number of columns in the game area.
 * @return Pointer to the 2D array representing the game area.
 */
char	**createArea(int ligne, size_t colonne);


#endif