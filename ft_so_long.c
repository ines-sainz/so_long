/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:55:54 by isainz-r          #+#    #+#             */
/*   Updated: 2024/06/24 09:28:23 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_destroy_window(t_game *game)
{
	ft_error(99, game);
	mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->wall != NULL)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->floor != NULL)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->collectibles != NULL)
		mlx_destroy_image(game->mlx, game->collectibles);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int	ft_key(int key, t_game *game)
{
	if (key == RIGHT && game->map[game->x_player][game->y_player + 1] != '1')
		ft_moves(key, game);
	else if (key == LEFT
		&& game->map[game->x_player][game->y_player - 1] != '1')
		ft_moves(key, game);
	else if (key == UP
		&& game->map[game->x_player - 1][game->y_player] != '1')
		ft_moves(key, game);
	else if (key == DOWN
		&& game->map[game->x_player + 1][game->y_player] != '1')
		ft_moves(key, game);
	else if (key == ESC)
		ft_destroy_window(game);
	return (0);
}

int	ft_so_long(t_game *game)
{
	int	height;
	int	width;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nProblem with the mlx", 2);
		return (ft_error(0, game));
	}
	mlx_get_screen_size(game->mlx, &width, &height);
	if (width < game->map_width * 64 || height < game->map_height * 64)
		return (free(game->mlx), ft_error(7, game));
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * 64,
			game->map_height * 64, "SO_LONG");
	if (!game->mlx_win)
	{
		ft_putstr_fd("Error\nProblem with the mlx", 2);
		return (free(game->mlx), ft_error(0, game));
	}
	ft_draw_map(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, ft_key, game);
	mlx_hook(game->mlx_win, 17, 1L << 17, ft_destroy_window, game);
	mlx_loop(game->mlx);
	return (0);
}
