/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:24:19 by bede-fre          #+#    #+#             */
/*   Updated: 2018/12/06 15:37:13 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_moving(t_all *all, double dir)
{
	t_coord		p;
	t_fcoord	sh;

	sh.x = (cos(all->p.a) >= 0.0) ? dir * HIT_BOX : -dir * HIT_BOX;
	sh.y = (sin(all->p.a) >= 0.0) ? -dir * HIT_BOX : dir * HIT_BOX;
	p.x = (sh.x + all->p.x + dir * ((cos(all->p.a) * all->speed)));
	p.y = (sh.y + all->p.y + -dir * ((sin(all->p.a) * all->speed)));
	all->p.x += (all->p.y >= 0.0 && to_map(all->p.y) < 32.0
		&& p.x >= HIT_BOX && p.x < (MAPX * (int)BLOCK_SIZE - HIT_BOX)
		&& !is_wall(all->rc.map[to_map((all->p.y - HIT_BOX))][to_map(p.x)])
		&& !is_wall(all->rc.map[to_map((all->p.y + HIT_BOX))][to_map(p.x)])) ?
		dir * (cos(all->p.a) * all->speed) : 0.0;
	all->p.y += (all->p.x >= 0.0 && to_map(all->p.x) < 32.0
		&& p.y >= HIT_BOX && p.y < (MAPY * (int)BLOCK_SIZE - HIT_BOX)
		&& !is_wall(all->rc.map[to_map(p.y)][to_map((all->p.x + HIT_BOX))])
		&& !is_wall(all->rc.map[to_map(p.y)][to_map((all->p.x - HIT_BOX))])) ?
		-dir * (sin(all->p.a) * all->speed) : 0.0;
}

void		ft_strafing(t_all *all, double dir)
{
	t_coord		p;
	t_fcoord	sh;

	sh.x = (sin(all->p.a) >= 0.0) ? -dir * HIT_BOX : dir * HIT_BOX;
	sh.y = (cos(all->p.a) >= 0.0) ? -dir * HIT_BOX : dir * HIT_BOX;
	p.x = (sh.x + all->p.x + -dir * (sin(all->p.a) * all->speed));
	p.y = (sh.y + all->p.y + -dir * (cos(all->p.a) * all->speed));
	all->p.x += (all->p.y >= 0.0 && to_map(all->p.y) < 32.0
		&& p.x >= HIT_BOX && p.x < (MAPX * (int)BLOCK_SIZE - HIT_BOX)
		&& !is_wall(all->rc.map[to_map((all->p.y - HIT_BOX))][to_map(p.x)])
		&& !is_wall(all->rc.map[to_map((all->p.y + HIT_BOX))][to_map(p.x)])) ?
		-dir * (sin(all->p.a) * all->speed) : 0.0;
	all->p.y += (all->p.x >= 0.0 && to_map(all->p.x) < 32.0
		&& p.y >= HIT_BOX && p.y < (MAPY * (int)BLOCK_SIZE - HIT_BOX)
		&& !is_wall(all->rc.map[to_map(p.y)][to_map((all->p.x + HIT_BOX))])
		&& !is_wall(all->rc.map[to_map(p.y)][to_map((all->p.x - HIT_BOX))])) ?
		-dir * (cos(all->p.a) * all->speed) : 0.0;
}

static void	action_zone(t_all *all)
{
	int	y;
	int	x;

	if (all->rc.map[to_map(all->p.y)][to_map(all->p.x)] == END)
		all->end = 1;
	if (all->rc.map[to_map(all->p.y)][to_map(all->p.x)] == LIGHTNING
		&& all->stamina < STAMINA_MAX)
	{
		all->stamina = STAMINA_MAX;
		all->rc.map[to_map(all->p.y)][to_map(all->p.x)] = FLOOR;
	}
	if (all->rc.map[to_map(all->p.y)][to_map(all->p.x)] == TP_E && (y = -1))
		while (++y < MAPY && (x = -1))
			while (++x < MAPX)
				if (all->rc.map[y][x] == TP_S)
				{
					all->p.x = x * (int)BLOCK_SIZE + 32;
					all->p.y = y * (int)BLOCK_SIZE + 32;
					Mix_PlayChannel(-1, all->sounds.teleport, 0);
				}
}

static void	ft_refresh_images(t_all *all)
{
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->fp.img, 0, 0);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->info.img, 0, 0);
	print_stamina_bar(&all->hud.stamina_bar, all->stamina);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win,
		all->hud.stamina_bar.img, BARX, BARY);
	if (all->s_jump)
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->hud.s_jump.img,
		INFOX / 2, WINY - 85);
	else if (all->speed == RUN_SPEED)
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->hud.s_run.img,
		INFOY / 2, WINY - 85);
	else if (all->speed == MOVE_SPEED)
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->hud.s_walk.img,
		INFOX / 2, WINY - 85);
	else if (all->speed == CROUCH_SPEED)
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win,
		all->hud.s_crouch.img, INFOX / 2, WINY - 85);
	else
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->hud.s_idle.img,
		INFOX / 2, WINY - 85);
	it_is_the_end(all);
}

int			ft_movements(t_all *all)
{
	refresh_events(all);
	jump_and_crouch(all);
	action_zone(all);
	stamina_control(all);
	mlx_destroy_image(all->ptr.mlx, all->info.img);
	init_image(all->ptr, &all->info, INFOX, INFOY);
	ft_print_all(all);
	ft_refresh_images(all);
	mute_sound(all);
	return (1);
}
