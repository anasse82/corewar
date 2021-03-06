/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instru.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:11:57 by tle-meur          #+#    #+#             */
/*   Updated: 2016/03/11 19:59:36 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compilo.h"

extern t_op	g_op_tab[17];

static int		is_real_instru(char **s)
{
	int	i;
	int	len;

	i = -1;
	while (g_op_tab[++i].instr_name)
	{
		len = ft_strlen(g_op_tab[i].instr_name);
		if (!ft_strncmp(*s, g_op_tab[i].instr_name, len))
		{
			if ((*s)[len] != ' ' && (*s)[len] != '\t')
				continue ;
			(*s) = jump_whitespaces((*s) + len);
			return (i);
		}
	}
	return (-1);
}

static t_list	*free_and_quit_arg(t_list **l)
{
	ft_lstdel(l, &my_arg_del);
	return (NULL);
}

static char		*my_strdup(char **s)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*s)[len] && (*s)[len] != SEPARATOR_CHAR && (*s)[len] != ' '
			&& !is_in_buf((*s)[len], COMMENT_CHARS) && (*s)[len] != '\t')
		len++;
	if (!(tmp = (char *)ft_strnew(len)))
		return (NULL);
	ft_memcpy(tmp, *s, len);
	len += ((*s)[len] == SEPARATOR_CHAR) ? 1 : 0;
	while ((*s)[len] && ((*s)[len] == ' ' || (*s)[len] == '\t'))
		len++;
	(*s) += len;
	return (tmp);
}

static t_list	*check_args(t_instr *i, char **s, int *byte, int id_arg)
{
	t_arg	add;
	t_list	*tmp;

	add.arg_type = 0;
	if ((tmp = NULL) || !**s || is_in_buf(**s, COMMENT_CHARS))
		return (i->args);
	if (id_arg >= g_op_tab[i->id_instr].params_nb)
		return (free_and_quit_arg(&i->args));
	if (check_register(i, s, id_arg) && ++(*byte))
		add.arg_type = REG_CODE;
	else if (check_direct(i, s, id_arg, &add))
	{
		add.arg_type |= DIR_CODE;
		(*byte) += (g_op_tab[i->id_instr].is_index) ? 2 : 4;
	}
	else if (check_indirect(i, s, id_arg) && ((*byte += 2)))
		add.arg_type = IND_CODE;
	else
		return (free_and_quit_arg(&i->args));
	if (!(add.arg_value = my_strdup(s))
		|| !(tmp = ft_lstnew(&add, sizeof(t_arg))))
		return (free_and_quit_arg(&i->args));
	ft_lstpush(&i->args, tmp);
	return (check_args(i, s, byte, id_arg + 1));
}

int				is_good_instru(t_env *e, char *s, int *byte)
{
	int		id;
	t_instr	add;
	t_list	*tmp;

	if ((id = is_real_instru(&s)) == -1)
		return (0);
	add.byte = (*byte)++;
	if (g_op_tab[id].code_byte)
		(*byte)++;
	add.id_instr = id;
	add.args = NULL;
	if (!(add.args = check_args(&add, &s, byte, 0)))
		return (0);
	if (!(tmp = ft_lstnew(&add, sizeof(t_instr))))
	{
		ft_lstdel(&add.args, &my_arg_del);
		return (0);
	}
	ft_lstpush(&e->instrs, tmp);
	return (1);
}
