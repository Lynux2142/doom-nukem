/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruellou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:11:47 by aruellou          #+#    #+#             */
/*   Updated: 2018/11/26 10:10:31 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	door_auto(char map[MAPY][MAPX], t_player p, t_point	i)
{
	if (map[i.y][i.x] == T_DOOR_I && door_timer(0.0, i.y, i.x, map) > 0.99)
		map[i.y][i.x] = T_DOOR_O;
	if (map[i.y][i.x] == T_DOOR_R && door_timer(0.0, i.y, i.x, map) < 0.01)
		map[i.y][i.x] = T_DOOR_C;
	if (map[i.y][i.x] == T_DOOR_O && sqrt(pow(((p.x / 64) - i.x), 2) + pow(((p.y / 64) - i.y), 2)) >= 5)
	{
		map[i.y][i.x] = T_DOOR_R;
		door_timer(-DOOR_SPEED, i.y, i.x, map);
	}

}

void	door_update(float timer[MAPY][MAPX], char map[MAPY][MAPX])
{
	int i;
	int j;
	char c;

	i = 0;
	while (i < MAPY)
	{
		j = 0;
		while (j < MAPX)
		{
			c = map[j][i];
			if (timer[i][j] >= 1 - DOOR_SPEED * 0.9)
				timer[i][j] = 1.0;
			else if (timer[i][j] <= DOOR_SPEED * 0.9)
				timer[i][j] = 0.0;
			else if (c == T_DOOR_I)
				timer[i][j] += DOOR_SPEED;
			else if (c == T_DOOR_R)
				timer[i][j] -= DOOR_SPEED;
			j++;
		}
		i++;
	}
}

float	door_timer(float add, int x, int y, char map[MAPY][MAPX])
{
	static float timer[MAPY][MAPX];
	static int	 i = 0;
	char c;

	c = map[x][y];

	if (i % 50000 == 0) {
		door_update(timer, map);
	}
	i++;
	if (c == T_DOOR_C || c == T_DOOR_I || c == T_DOOR_R || c == T_DOOR_O)
	{
		if (c == T_DOOR_C)
			timer[y][x] = 0.0;
		else if (c == T_DOOR_O)
			timer[y][x] = 1.0;
		else if (add) 
			timer[y][x] += add;
		return (timer[y][x]);
	}
	return (0.0);
}

void	door_open(t_all *all)
{
	all->a = all->p.a - ft_rad((((WINX / 2) - 1) - (WINX / 2) - 1) * RAY_ANGLE);
	ft_fp_hori(&all->rc.ray_h, &all->p, all->rc.map, all->a);
	ft_fp_vert(&all->rc.ray_v, &all->p, all->rc.map, all->a);
	if (all->rc.ray_h.dist != all->rc.ray_h.dist ||
		all->rc.ray_v.dist != all->rc.ray_v.dist)
		all->rc.ray = (all->rc.ray_h.dist != all->rc.ray_h.dist) ?
		all->rc.ray_v : all->rc.ray_h;
	else
		all->rc.ray = (all->rc.ray_h.dist <= all->rc.ray_v.dist) ?
		all->rc.ray_h : all->rc.ray_v;
	if (all->rc.map[to_map(all->rc.ray.y)][to_map(all->rc.ray.x)] == T_DOOR_C
	&& all->rc.ray.dist <= 100)
	{
		Mix_PlayChannel(-1, all->sounds.opendoor, 0);
		all->rc.map[to_map(all->rc.ray.y)][to_map(all->rc.ray.x)] = T_DOOR_I;
		door_timer(DOOR_SPEED * 2, to_map(all->rc.ray.y), to_map(all->rc.ray.x),
			all->rc.map);
	}
	all->lens -= ft_rad(RAY_ANGLE) * all->keys_tab[KEY_H];
	all->a -= ft_rad(RAY_ANGLE);
}