/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:52:14 by ael-hana          #+#    #+#             */
/*   Updated: 2016/03/28 00:49:10 by ecousine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"


unsigned int		ldi(t_env *data, t_process *process)
{
	unsigned char	*arena;
	int				*tab;
	int				value;
	int				index;
	int				reg_dest;

	if (data->debug)
		ft_printf("Start of LDI\n");
	arena = data->arena;
	if ((tab = get_op_args(arena, process)) == NULL)
		return (update_pc_pos_on_failure(arena, process));
	reg_dest = tab[2];
	if (data->debug)
		ft_printf("Arg 1 : %#x, Arg 2 : %#x\n Arg 3 : %#x\n", tab[0], tab[1]);
	if (get_dir_value(arena, process, tab) == 0)
		return (update_pc_pos_on_failure(arena, process));

	if (get_ind_value(data->arena, process, tab, 1) == 0)
		return (update_pc_pos_on_failure(arena, process));

	if (data->debug)
		ft_printf("Arg 1 : %#x, Arg 2 : %#x\n Arg 3 : %#x\n", tab[0], tab[1]);
	index = (tab[0] + tab[1]) % IDX_MOD;
	value = arena[(process->position + index++) % MEM_SIZE];
	value = value << 8;
	value += arena[(process->position + index++) % MEM_SIZE];
	value = value << 8;
	value += arena[(process->position + index++) % MEM_SIZE];
	value = value << 8;
	value += arena[(process->position + index) % MEM_SIZE];
	if (reg_dest >= 1 && reg_dest <= 16)
		process->reg[reg_dest - 1] = value;
	else
		return (update_pc_pos_on_failure(arena, process));
	update_pc_pos(data->arena, process);
	if (data->debug)
		ft_printf("End of LDI\n");
	return (1);
}
/*
   unsigned int		ldi(unsigned char *arena, t_process *process)
   {
   const int		i = ++process->position % MEM_SIZE;
   int				tab[3];

   if ((arena[i] & 0b00001100) != 0b00000100 || ((arena[i] & 0b00110000) !=
   0b00100000 && (arena[i] & 0b00110000) != 0b00010000) ||
   !(arena[i] & 0b11000000))
   return (0);
   if ((tab[0] = recup_val((arena[i] >> 6) & 3, arena, &process->position))
   > 16 && ((arena[i] >> 6) & 3) == 1)
   return (0);
   (((arena[i] >> 6) & 3) == 1) ? tab[0] = process->reg[tab[0]] : 0;
   if ((tab[1] = recup_val((arena[i] >> 4) & 3, arena, &process->position))
   > 16 && ((arena[i] >> 4) & 3) == 1)
   return (0);
   (((arena[i] >> 4) & 3) == 1) ? tab[1] = process->reg[tab[1]] : 0;
   if ((tab[2] = recup_val((arena[i] >> 2) & 3, arena, &process->position))
   > 16 && ((arena[i] >> 2) & 3) == 1)
   return (0);
   process->reg[tab[2]] = arena[((i - 1) + ((tab[0] + tab[1]) % IDX_MOD))
   % MEM_SIZE];
//return (process->carry = process->reg[tab[2]] == 0 ? 1 : 0);
return (0);
}*/
