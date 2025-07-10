/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:27:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 12:43:24 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_error	wait_next_line(char **input, char quote);
static void		append_line(char **input, t_error *err);
static int		add_nl(char **input, t_error *lex_error);
static void		print_unexpected(char quote);

void	hold_for_more_input(char **input, char *quote, t_error *lex_error)
{
	if (!ft_strchr(*input, '\n'))
		add_nl(input, lex_error);
	if (*lex_error)
		return ;
	while (has_unclosed_quotes(*input, quote))
	{
		*lex_error = wait_next_line(input, *quote);
		if (*lex_error == MALLOC_ERR || *lex_error == INTERRUPTED)
			return ;
		if (*lex_error == SYNTAX_ERR)
			break ;
	}
	clean_str(input);
}

static t_error	wait_next_line(char **input, char quote)
{
	t_error				err;
	struct sigaction	sa;
	struct sigaction	old_sa;

	err = 0;
	if (set_gnl_handler(&sa, &old_sa) == -1)
	{
		ft_free((void **)input);
		return (EXIT_FAILURE);
	}
	append_line(input, &err);
	if (sigaction(SIGINT, &old_sa, NULL) == -1)
	{
		if (*input)
			ft_free((void **)input);
		return (EXIT_FAILURE);
	}
	if (err == INTERRUPTED && *input)
		ft_free((void **)input);
	if (err == SYNTAX_ERR)
		print_unexpected(quote);
	return (err);
}

static void	print_unexpected(char quote)
{
	if (quote == '\'')
		print_error(NULL, NULL,
			"unexpected EOF while looking for matching `''");
	else
		print_error(NULL, NULL,
			"unexpected EOF while looking for matching `\"'");
}

static void	append_line(char **input, t_error *err)
{
	char	*line;
	char	*new_line;

	new_line = NULL;
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (check_gnl_interrupt(&line, err))
		return ;
	if (!line)
	{
		clean_str(input);
		*err = SYNTAX_ERR;
		return ;
	}
	new_line = ft_strjoin(*input, line);
	ft_free((void **)&line);
	ft_free((void **)input);
	if (!new_line)
	{
		*err = MALLOC_ERR;
		*input = NULL;
	}
	else
		*input = new_line;
}

static int	add_nl(char **input, t_error *lex_error)
{
	char	*new_line;
	int		i;

	new_line = ft_calloc(ft_strlen(*input) + 2, sizeof(char));
	if (!new_line)
	{
		ft_free((void **)input);
		*lex_error = MALLOC_ERR;
		return (0);
	}
	i = -1;
	while ((*input)[++i])
		new_line[i] = (*input)[i];
	new_line[i++] = '\n';
	new_line[i] = '\0';
	ft_free((void **)input);
	*input = new_line;
	return (1);
}
