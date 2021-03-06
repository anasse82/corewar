/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousine <ecousine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 17:10:38 by ecousine          #+#    #+#             */
/*   Updated: 2016/04/01 14:43:17 by ecousine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "function.h"

void	init_data(t_env *data)
{
	data->i = 1;
	data->dump = 2147483647;
	data->nb_players = 0;
	data->player_list = NULL;
	data->process_list = NULL;
	data->total_live = 0;
	data->cycle_of_last_verif = 0;
	data->cycle = 0;
	data->cycle_to_die = CYCLE_TO_DIE;
	data->live_last_verif = 0;
	data->visual = 0;
	data->cycle_per_sec = 100;
	data->debug = 0;
}

int		main(int ac, char **av)
{
	t_env		data;

	init_data(&data);
	parse_flags(ac, av, &data);
	parse_players(ac, av, &data);
	create_arena(&data);
	place_players(&data);
	print_player_introduction(data.player_list);
	start_game(&data);
	if (data.visual)
	{
		print_arena(&data);
		print_info(&data);
	}
	print_winner(&data);
	ft_lstdel(&data.player_list, &free_player);
	ft_lstdel(&data.process_list, &free_process);
	ft_memdel((void**)&data.arena);
	ft_memdel((void**)&data.arena_owner);
	return (0);
}
