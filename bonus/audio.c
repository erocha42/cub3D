/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:36:50 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/14 17:03:57 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "cub3d.h"
#include "miniaudio.h"

void	init_audio(t_game *game)
{
	ma_result result;
	ma_result result2;

	game->has_audio = 0;
	if (ma_engine_init(NULL, &game->audio_engine) != MA_SUCCESS)
		return ;
	result = ma_sound_init_from_file(&game->audio_engine, "./GMT.wav", 0, NULL,
			NULL, &game->monster_sound);
	result2 = ma_sound_init_from_file(&game->audio_engine, "./oh-tgl-prof.wav",
			0, NULL, NULL, &game->jumpscare_sound);
	if (result != MA_SUCCESS || result2 != MA_SUCCESS)
	{
		ma_engine_uninit(&game->audio_engine);
		return ;
	}
	game->has_audio = 1;
	ma_sound_set_looping(&game->monster_sound, MA_TRUE);
	ma_sound_start(&game->monster_sound);
}