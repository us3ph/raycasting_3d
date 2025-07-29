/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <yanflous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:51:36 by yanflous          #+#    #+#             */
/*   Updated: 2025/07/28 13:53:19 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int key_code)
{
	t_game	*game;

	game = g_game();
	if (key_code == ESC_KEY)
		game_exit(EXIT_SUCCESS, NULL);
	if (key_code == UP_KEY)
		game->direction.walk_dir = FORWARD;
	if (key_code == DOWN_KEY)
		game->direction.walk_dir = BACKWARD;
	if (key_code == LEFT_KEY)
		game->direction.side_dir = LEFT;
	if (key_code == RIGHT_KEY)
		game->direction.side_dir = RIGHT;
	if (key_code == LEFT_ARROW)
		game->direction.turn_dir = TURN_LEFT;
	if (key_code == RIGHT_ARROW)
		game->direction.turn_dir = TURN_RIGHT;
	return (0);
}

void	handle_key_press(t_game *game)
{
	t_direction	*dir;

	dir = &game->direction;
	if (dir->walk_dir == FORWARD)
		upgrade_player_dir(game, FORWARD, false);
	if (dir->walk_dir == BACKWARD)
		upgrade_player_dir(game, BACKWARD, false);
	if (dir->side_dir == LEFT)
		upgrade_player_dir(game, LEFT, true);
	if (dir->side_dir == RIGHT)
		upgrade_player_dir(game, RIGHT, true);
	if (dir->turn_dir == TURN_LEFT)
		upgrade_player_s_dir(game, -ROT_SPEED);
	if (dir->turn_dir == TURN_RIGHT)
		upgrade_player_s_dir(game, ROT_SPEED);
}

int	key_release(int key_code)
{
	t_direction	*dir;

	dir = &g_game()->direction;
	if (key_code == UP_KEY || key_code == DOWN_KEY)
		dir->walk_dir = 0;
	else if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
		dir->side_dir = 0;
	else if (key_code == LEFT_ARROW || key_code == RIGHT_ARROW)
		dir->turn_dir = 0;
	return (0);
}
