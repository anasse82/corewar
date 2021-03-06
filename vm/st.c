/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 20:32:34 by ael-hana          #+#    #+#             */
/*   Updated: 2016/03/31 18:39:31 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "function.h"

unsigned int		st(t_env *data, t_process *process)
{
	unsigned char	*arena;
	int				*tab;
	short			index;

	arena = data->arena;
	if ((tab = get_op_args(arena, process)) == NULL)
		return (update_pc_pos_on_failure(arena, process, &tab));
	index = tab[1];
	if (get_dir_value(arena, process, tab) == 0)
		return (update_pc_pos_on_failure(arena, process, &tab));
	if (get_ind_value(arena, process, tab, 1) == 0)
		return (update_pc_pos_on_failure(arena, process, &tab));
	write_arena(data, process, index % IDX_MOD, tab[0]);
	update_pc_pos(data->arena, process);
	ft_memdel((void **)&tab);
	return (1);
}
