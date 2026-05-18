/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:00:39 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/18 18:28:44 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	check_jumpscare(t_game *game)
{
	double	dist;

	dist = sqrt(pow(game->player.x - game->sprite.x, 2) + pow(game->player.y
				- game->sprite.y, 2));
	if (dist < 0.3)
	{
		jumpscare(game);
		ma_sound_set_volume(&game->monster_sound, 0);
		ma_sound_start(&game->jumpscare_sound);
		usleep(2000000);
		clean_exit(game, NO_ERROR);
	}
}

static void	update_monster_audio(t_game *game)
{
	int		bfs_dist;
	float	volume;

	bfs_dist = game->heatmap[(int)game->sprite.y][(int)game->sprite.x];
	if (bfs_dist > 15 || bfs_dist < 0)
		volume = 0.0f;
	else
		volume = 1.0f - ((float)bfs_dist / 15.0f);
	if (volume < 0.0f)
		volume = 0.0f;
	if (volume > 1.0f)
		volume = 1.0f;
	if (game->has_audio == 1)
		ma_sound_set_volume(&game->monster_sound, volume);
}

static void	move_sprite_to_target(t_game *g, double target_x, double target_y)
{
	double	dist;
	double	stepx;
	double	stepy;

	dist = sqrt(pow(target_x - g->sprite.x, 2) + pow(target_y - g->sprite.y,
				2));
	if (dist > 0.05)
	{
		stepx = (target_x - g->sprite.x) / dist * 0.05;
		stepy = (target_y - g->sprite.y) / dist * 0.05;
		g->sprite.x += stepx;
		g->sprite.y += stepy;
	}
}

void	update_sprite(t_game *game)
{
	int		t_xy[2];
	double	target[2];

	check_jumpscare(game);
	heatmap(game);
	bfs(game);
	update_monster_audio(game);
	if ((int)game->sprite.x == (int)game->player.x
		&& (int)game->sprite.y == (int)game->player.y)
	{
		target[0] = game->player.x;
		target[1] = game->player.y;
	}
	else
	{
		get_next_step(game, (int)game->sprite.x, (int)game->sprite.y, t_xy);
		target[0] = t_xy[0] + 0.5;
		target[1] = t_xy[1] + 0.5;
	}
	move_sprite_to_target(game, target[0], target[1]);
}
