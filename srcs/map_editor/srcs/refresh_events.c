/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:49:10 by lguiller          #+#    #+#             */
/*   Updated: 2018/12/03 13:45:24 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	change_sound(t_env *env, int *sound)
{
	if (win_to_map(env->mouse.x) == win_to_map(env->buttons[B_SOUND].pos.x) &&
		win_to_map(env->mouse.y) == win_to_map(env->buttons[B_SOUND].pos.y))
		*sound = (*sound == 1) ? 0 : 1;
	if (*sound == 1)
		Mix_VolumeMusic(MIX_MAX_VOLUME);
	else
		Mix_VolumeMusic(0);
}

static void	change_colision(t_env *env, char *object, int *colision)
{
	if (win_to_map(env->mouse.x) >= win_to_map(env->buttons[COLISION].pos.x) &&
		win_to_map(env->mouse.x) <=
		win_to_map(env->buttons[COLISION].pos.x) + 2 &&
		win_to_map(env->mouse.y) == win_to_map(env->buttons[COLISION].pos.y))
	{
		*colision = TRUE;
		if (*object == T_AS || *object == T_BS ||
			*object == T_CS || *object == T_DS)
			*object -= 32;
	}
	else if (win_to_map(env->mouse.x) >=
		win_to_map(env->buttons[NO_COLISION].pos.x) &&
		win_to_map(env->mouse.x) <=
		win_to_map(env->buttons[NO_COLISION].pos.x) + 2 &&
		win_to_map(env->mouse.y) == win_to_map(env->buttons[NO_COLISION].pos.y))
	{
		*colision = FALSE;
		if (*object == T_A || *object == T_B ||
			*object == T_C || *object == T_D)
			*object += 32;
	}
}

static void	change_object(t_env *env, char *object)
{
	char x;

	x = chose_object(env->buttons, env->mouse.x, env->mouse.y, env->colision);
	if (x != -1)
		*object = x;
}

/*
** GESTION DES ACTIONS A EFFECTUER LORS D'UN EVENEMENT CLAVIER
*/

void		refresh_events(t_env *env)
{
	if (env->keys[B_LEFT])
	{
		change_sound(env, &env->sound);
		change_colision(env, &env->object, &env->colision);
		change_object(env, &env->object);
		modif_map(env);
	}
	if (env->keys[K_RENDER])
	{
		write_file(env->file_name, env->map);
		clear(env, NULL, 0);
	}
	if (env->keys[K_LEAKS])
		system("leaks editor | grep 'leaked bytes'");
	if (env->keys[K_MUTE])
		env->sound = (env->sound) ? 0 : 1;
	start_draw(env);
}
