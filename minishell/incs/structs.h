/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:49:19 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/14 14:55:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// Lexing phase uses t_lexer and t_token
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token		*tokens;
	int			i;
	char		*input;
	t_error		error;
	int			paren_c;
}	t_lexer;

// For storing the env variables
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// For storing commands and arguments
typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

//	For storing redirection info in command nodes
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	char			*hd_delimit;
	char			*hd_content;
	int				hd_preprocessed_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_fds
{
	int				input_fd;
	int				output_fd;
	int				*new_in;
	int				*new_out;
}	t_fds;

typedef struct s_redir_fds
{
	int				input_fd;
	int				output_fd;
	int				*new_in;
	int				*new_out;
}	t_redir_fds;

//	For the AST that the execution uses
//	Node can access one of these unions based on its type;
//	cmd for commands, binary for ||, &&, |
typedef struct s_node
{
	t_node_type	type;
	union u_data
	{
		struct s_cmd
		{
			t_args			*args;
			t_redir			*redirects;
		}	command;
		struct s_binary
		{
			struct s_node	*left;
			struct s_node	*right;
			char			*operator;
		}	binary;
	}	data;
}	t_node;

// For passing around the shell data
typedef struct s_shell
{
	struct s_env	*env;
	struct s_node	*ast;
	t_error			exit_status;
	bool			exit;
	struct termios	initial_term;
}	t_shell;

//	Helper structure for env expansion
typedef struct s_split
{
	int	i;
	int	j;
	int	count;
	int	in_squote;
	int	in_dquote;
}	t_split;

//	Wildcard expansion helper structure
typedef struct s_index
{
	int	s_i;
	int	star_pat_i;
	int	star_s_i;
}	t_index;

//	Pattern matching for wildcards
typedef struct s_pattern
{
	char	*str;
	int		i;
	int		in_squote;
	int		in_dquote;
	char	current;
}	t_pattern;

typedef struct s_pipe
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status_left;
	int		status_right;
	int		input_fd;
	int		output_fd;
	t_node	*node;
}			t_pipe;

#endif
