/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:42:58 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 12:46:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR,
	T_PAREN_L,
	T_PAREN_R,
	T_IN,
	T_TRUNCATE,
	T_APPEND,
	T_HEREDOC,
	T_EOF
}	t_token_type;

typedef enum e_error
{
	SUCCESS = 0,
	MALLOC_ERR = 12,
	SYNTAX_ERR = 2,
	INTERRUPTED = 130,
}	t_error;

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_LOGICAL_OP,
	N_SUBSHELL
}	t_node_type;

typedef enum e_builtin_type
{
	NOT_BUILTIN,
	BUILTIN_NO_FORK,
	BUILTIN_FORK
}	t_builtin_type;

#endif
