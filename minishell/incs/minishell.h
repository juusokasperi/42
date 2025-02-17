/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:47:44 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/14 14:51:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <termios.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include "libft.h"
# include "enums.h"
# include "structs.h"
# include "init.h"
# include "debug.h"
# include "parsing.h"
# include "execution.h"

# define MSH "\001\033[38;5;186m\002minishell$\001\033[0m\002 "

extern volatile sig_atomic_t	g_signal;

#endif
