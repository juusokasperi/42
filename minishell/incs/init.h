/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:49:34 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 12:44:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

/*	***************	*/
/*		INIT		*/
/*	***************	*/
void			noninteractive_mode(t_shell *sh);
//	init.c
void			init_sh(t_shell *sh, char **env);
int				disable_echo(void);
int				restore_original_termios(t_shell *sh);
//	env/env_init.c
t_env			*init_env(t_shell *sh, char **env);
//	env/env_tools.c
t_env			*find_env_variable(t_env *env, char *key);
int				add_env_variable(t_env **env, char *key, char *value);
int				update_env_value(t_env *env, char *key, char *value);
char			*find_env_value(t_env *env, char *key);
//	env/lst_tools.c
t_env			*free_env_list(t_env *lst);
t_env			*envlst_new(char *key, char *value);
int				envadd_back(t_env **lst, t_env *new);
//	readline_loop.c
void			interactive_mode(t_shell *sh);
//	unclosed_quotes.c
void			hold_for_more_input(char **input, char *quote,
					t_error *lex_error);
//	unclosed_quotes_utils.c
int				has_unclosed_quotes(char *input, char *quote);
int				set_gnl_handler(struct sigaction *sa,
					struct sigaction *old_handler);
void			gnl_sig_handler(int signum, siginfo_t *info, void *context);
int				check_gnl_interrupt(char **line, t_error *err);
void			clean_str(char **input);

#endif
