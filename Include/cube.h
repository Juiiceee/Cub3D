/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/18 15:18:41 by mda-cunh         ###   ########.fr       */
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

# define WIN_WIDTH 960
# define WIN_HEIGHT 560
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

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_coord_int
{
	int			x;
	int			y;
}					t_coord_int;

typedef struct s_game_mesure
{
	int	line;
	int	column;
}	t_game_mesure;

typedef struct s_game_pos
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_game_pos;

typedef struct s_game_ray
{
	double		cameraX;
	t_coord		rayDir;
	t_coord		sideDist;
	t_coord		deltaDist;
	t_coord_int	map;
	t_coord_int step;
	double		perpWallDist;
	int			lineHeight;
	int			drawStart;
	int 		drawEnd;
	t_coord_int	start_point;
	t_coord_int	end_point;
	int			side;
}	t_game_ray;

typedef struct s_game_texture
{
    void *img;
    char *data;
    int width;
    int height;
    int bpp;
    int size_line;
    int endian;
} t_game_texture;


typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**area;
	t_game_mesure	mesure;
	t_game_pos		pos;
	t_game_texture	texture;
	t_game_texture	img;
	t_game_texture	floor_texture;
    t_game_texture	ceiling_texture;
	t_game_ray		ray;
}	t_game;

//mapChecker.c

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

// mapCheckerInput.c

/**
 * @brief Checks all game elements for validity.
 *
 * This function checks all game elements, including walls, characters, and other characters,
 * to ensure they are valid and meet the required criteria.
 *
 * @param game The game structure containing all game elements.
 * @return Returns 0 if all elements are valid, 1 otherwise.
 */
int	checkAll(t_game *game);
/**
 * @brief Checks for the presence of other characters.
 *
 * This function checks for the presence of characters other than walls and players
 * in the game map.
 *
 * @param game The game structure containing all game elements.
 * @return Returns 0 if there are no other characters, 1 otherwise.
 */
int	checkOtherChar(t_game *game);
/**
 * @brief Checks for the presence of walls.
 *
 * This function checks for the presence of walls in the game map.
 *
 * @param game The game structure containing all game elements.
 * @return Returns 0 if there are walls, 1 otherwise.
 */
int	checkWall(t_game *game);
/**
 * @brief Checks for the presence of a player.
 *
 * This function checks for the presence of a player in the game map.
 *
 * @param game The game structure containing all game elements.
 * @return Returns 0 if there is a player, 1 otherwise.
 */
int	checkPlayer(t_game *game);

//mapCreate.c

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
/**
 * @brief Displays the position of the player in the game.
 *
 * This function is responsible for displaying the position of the player
 * in the game at the specified coordinates (x, y).
 *
 * @param game A pointer to the game structure.
 * @param x The x-coordinate of the player's position.
 * @param y The y-coordinate of the player's position.
 */
void	putpos(t_game *game, int x, int y);

// mapSize.c

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

// mapUtils.c

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
/**
 * @brief Frees the memory allocated for the tab in the game structure.
 * 
 * This function is responsible for freeing the memory allocated for the tab
 * in the game structure. It should be called when the tab is no longer needed
 * to avoid memory leaks.
 * 
 * @param game A pointer to the game structure.
 */
void	freeTab(t_game *game);


// get_next_line.c

/**
 * Reads a line from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return A pointer to the line read from the file descriptor, or NULL if there are no more lines to read or an error occurs.
 */
char	*get_next_line(int fd);

#endif