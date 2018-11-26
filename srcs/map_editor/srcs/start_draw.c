/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:06:22 by lguiller          #+#    #+#             */
/*   Updated: 2018/11/26 14:59:07 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		set_background(SDL_Surface *surface, Uint32 col)
{
	t_point p;

	p.y = -1;
	while (++p.y < WIN_HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIN_WIDTH)
			fill_px(surface, p.x, p.y, col);
	}
}

static void		print_texture(t_env *env)
{
	SDL_Rect	rect;
	int			i;

	i = -1;
	while (++i <= ICE)
	{
		rect = create_rect(env->buttons[i].rect.x + 2,
			env->buttons[i].rect.y + 2, env->buttons[i].rect.w - 3,
			env->buttons[i].rect.h - 3);
		SDL_RenderCopy(env->renderer, env->buttons[i].texture, NULL, &rect);
	}
	rect = create_rect(env->buttons[B_ERASER].rect.x + 2,
		env->buttons[B_ERASER].rect.y + 2, env->buttons[B_ERASER].rect.w - 3,
		env->buttons[B_ERASER].rect.h - 3);
	SDL_RenderCopy(env->renderer, env->buttons[B_ERASER].texture, NULL, &rect);
	rect = create_rect(env->buttons[B_DOOR].rect.x + 2,
		env->buttons[B_DOOR].rect.y + 2, env->buttons[B_DOOR].rect.w - 3,
		env->buttons[B_DOOR].rect.h - 3);
	SDL_RenderCopy(env->renderer, env->buttons[B_DOOR].texture, NULL, &rect);
	rect = create_rect(env->buttons[B_SOUND].rect.x,
		env->buttons[B_SOUND].rect.y, env->buttons[B_SOUND].rect.w,
		env->buttons[B_SOUND].rect.h);
	SDL_RenderCopy(env->renderer, env->buttons[(env->sound == 1) ?
		B_SOUND : B_MUTE].texture, NULL, &rect);
}

/*
** LANCEMENT DES FONCTIONS D'EDITION DE SURFACE
*/

void			start_draw(t_env *env)
{
	SDL_Surface *surface;

	SDL_RenderClear(env->renderer);
	surface = init_surface(env);
	set_background(surface, WHITE);
	set_text(surface, env);
	make_grid(surface);
	print_map(surface, env->map);
	print_buttons(env, surface, env->object, env->colision);
	print_view(surface, env);
	print_texture(env);
	SDL_RenderPresent(env->renderer);
}
