/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:30:09 by lguiller          #+#    #+#             */
/*   Updated: 2018/11/13 11:25:54 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static Uint32	col_wall(char object)
{
	if (object == T_A)
		return (T_A_COL);
	else if (object == T_B)
		return (T_B_COL);
	else if (object == T_C)
		return (T_C_COL);
	else if (object == T_D)
		return (T_D_COL);
	else if (object == T_AS)
		return (T_AS_COL);
	else if (object == T_BS)
		return (T_BS_COL);
	else if (object == T_CS)
		return (T_CS_COL);
	else if (object == T_DS)
		return (T_DS_COL);
	else if (object == SECRET)
		return (SECRET_COL);
	else if (object == TP_S)
		return (TP_S_COL);
	else if (object == TP_E)
		return (TP_E_COL);
	else if (object == START)
		return (START_COL);
	return (0);
}

void			print_map(SDL_Surface *surface, char map[MAP_HEIGHT][MAP_WIDTH])
{
	t_point p;

	p.y = -1;
	while (++p.y < MAP_HEIGHT)
	{
		p.x = -1;
		while (++p.x < MAP_WIDTH)
			if (map[p.y][p.x] != ' ')
				fill_rect(surface, point_to_win(p), col_wall(map[p.y][p.x]));
	}
}
