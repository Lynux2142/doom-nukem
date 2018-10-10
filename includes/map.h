/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:29:52 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/10 14:21:35 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "doom.h"

# define MAP_WIDTH 200
# define MAP_HEIGHT 200

typedef struct	s_wall
{
	int			nextzone;
	char		type; // clip / noclip / ...?
	t_vec		origin;
}				t_wall;

typedef struct	s_zone
{
	t_wall		**walls;
}				t_zone;

#endif
