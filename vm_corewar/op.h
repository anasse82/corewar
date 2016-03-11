/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/03/11 19:55:11 by ael-hana         ###   ########.fr       */
=======
/*   Updated: 2016/03/11 17:30:21 by ecousine         ###   ########.fr       */
>>>>>>> 003dd53417bc2afa3d8b7394c033a6b3d8a83a0e
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "../libft/libft.h"

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHARS		"#;"
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

typedef char		t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3
# define READ_SIZE			42


typedef struct		s_env
{
	int		i;
	int		dump;
}					t_env;

typedef struct		s_process
{
	int				carry;
	int				reg[16];
	int				i;
	unsigned char	*ptr;
	s_process		*next;
}					t_process;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	unsigned char	*inst;
	char			comment[COMMENT_LENGTH + 1];
	t_process		*list_process;
}					t_header;

typedef struct		s_op
{
	char	*instr_name;
	int		params_nb;
	int		params_type[3];
	int		opcode;
	int		cycles_nb;
	char	*comment;
	int		encod; //byte encodage
	int		index; //index = 2 sans = 4
}					t_op;

#endif
