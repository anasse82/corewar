/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousine <ecousine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 17:28:24 by ecousine          #+#    #+#             */
/*   Updated: 2016/03/31 15:03:03 by ecousine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "function.h"

t_process	*create_process(t_process *father_process, t_header *player,
		int position)
{
	t_process	*new_process;

	if (!(new_process = malloc(sizeof(t_process))))
		error_msg("CAN'T MALLOC\n");
	if (father_process == NULL)
	{
		new_process->player = player;
		new_process->cycle = -1;
		new_process->op = 0;
		new_process->carry = 0;
		ft_bzero(new_process->reg, sizeof(int) * 16);
		new_process->reg[0] = 0xFFFFFFFF - (player->n - 1);
		new_process->alive = 1;
		new_process->last_alive = 0;
	}
	else
	{
		*new_process = *father_process;
		new_process->cycle = -1;
		new_process->position = position;
	}
	return (new_process);
}

void		get_inst(t_process *process, unsigned char *arena)
{
	int		i;

	i = -1;
	while (g_op_tab[++i].opcode)
	{
		if (g_op_tab[i].opcode == arena[process->position])
		{
			process->cycle = g_op_tab[i].cycles_nb - 2;
			process->op = g_op_tab[i].opcode;
			return ;
		}
	}
	process->position = (process->position + 1) % MEM_SIZE;
}
