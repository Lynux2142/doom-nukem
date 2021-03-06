/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:06:22 by lguiller          #+#    #+#             */
/*   Updated: 2018/12/10 18:14:57 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		set_background(SDL_Surface *surface)
{
	t_point			p;
	const int		d = 2;
	const t_point	px = {map_to_win(33), map_to_win(50)};
	const t_point	py = {map_to_win(0), map_to_win(32)};

	p.y = -1;
	while (++p.y < WIN_HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIN_WIDTH)
			fill_px(surface, p.x, p.y, WHITE);
	}
	p.y = py.x;
	while (++p.y < py.y)
	{
		p.x = px.x;
		while (++p.x < px.y)
		{
			if (p.x <= (px.x + d) || p.x >= (px.y - d) || p.y <= (py.x + d)
				|| p.y >= (py.y - d))
				fill_px(surface, p.x, p.y, BLACK);
			else
				fill_px(surface, p.x, p.y, LIGHT_GREY);
		}
	}
}

static void		print_texture2(SDL_Surface *surface, t_env *env, SDL_Rect rect)
{
	rect = create_rect(env->buttons[B_DOOR].rect.x,
		env->buttons[B_DOOR].rect.y, env->buttons[B_DOOR].rect.w,
		env->buttons[B_DOOR].rect.h);
	scale_surface(surface, env->buttons[B_DOOR].surface, &rect);
	rect = create_rect(env->buttons[B_SOUND].rect.x,
		env->buttons[B_SOUND].rect.y, env->buttons[B_SOUND].rect.w,
		env->buttons[B_SOUND].rect.h);
	scale_surface(surface, env->buttons[(env->sound == 1) ?
		B_SOUND : B_MUTE].surface, &rect);
}

static void		print_texture(SDL_Surface *surface, t_env *env)
{
	SDL_Rect	rect;
	int			i;

	i = -1;
	while (++i <= B_GIRL)
	{
		rect = create_rect(env->buttons[i].rect.x + 2,
			env->buttons[i].rect.y + 2, env->buttons[i].rect.w - 3,
			env->buttons[i].rect.h - 3);
		scale_surface(surface, env->buttons[i].surface, &rect);
	}
	rect = create_rect(env->buttons[B_ERASER].rect.x + 2,
		env->buttons[B_ERASER].rect.y + 2, env->buttons[B_ERASER].rect.w - 3,
		env->buttons[B_ERASER].rect.h - 3);
	scale_surface(surface, env->buttons[B_ERASER].surface, &rect);
	print_texture2(surface, env, rect);
}

/*
** LANCEMENT DES FONCTIONS D'EDITION DE SURFACE
*/

void			start_draw(t_env *env)
{
	SDL_Surface *surface;

	SDL_RenderClear(env->renderer);
	surface = init_surface(env, WIN_WIDTH, WIN_HEIGHT);
	set_background(surface);
	make_grid(surface);
	print_buttons(env, surface, env->object, env->colision);
	set_text(surface, env);
	print_map(surface, env->map, env);
	print_texture(surface, env);
	print_view(surface, env);
	SDL_RenderPresent(env->renderer);
}
