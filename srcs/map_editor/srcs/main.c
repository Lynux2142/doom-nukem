/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:18:35 by lguiller          #+#    #+#             */
/*   Updated: 2018/11/19 10:11:34 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** INITIALISATION DE ENV ET LANCEMENT DE LA BOUCLE DES EVENTS
*/

static void	ft_loop(char *file_name)
{
	int			loop;
	t_env		env;
	SDL_Event	event;

	loop = 1;
	init(&env, file_name);
	start_draw(&env);
	while (loop)
	{
		while (SDL_PollEvent(&event))
			events(event, &loop, &env);
		check_frame();
	}
	SDL_RenderClear(env.renderer);
	SDL_DestroyWindow(env.window);
	TTF_CloseFont(env.font);
	TTF_Quit();
	SDL_Quit();
}

int			main(int ac, char **av)
{
	if (ac == 2)
		ft_loop(av[1]);
	else if (ac == 3 && av[1][0] == '-' && av[1][1] == 'n' && av[1][2] == '\0')
	{
		create_new_file(av[2]);
		ft_loop(av[2]);
	}
	else
	{
		ft_puterror("usage: ./editor [-n] [map_name ...]");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
