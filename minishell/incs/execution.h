/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:51:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 13:49:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*	***************	*/
/*	EXECUTION		*/
/*	***************	*/
//	execution
int				execute_command(t_shell *sh, t_node *node,
					int input_fd, int output_fd);
int				execute_node(t_shell *sh, t_node *node,
					int input_fd, int output_fd);
int				execute_pipe(t_shell *sh, t_node *node,
					int input_fd, int output_fd);
int				execute_redirect(t_shell *sh, t_node *node,
					int input_fd, int output_fd);
int				execute_subshell(t_shell *sh, t_node *node,
					int input_fd, int output_fd);
int				execute_logical(t_shell *sh, t_node *node,
					int input_fd, int output_fd);
//	execution/execute_builtin.c
t_builtin_type	get_builtin_type(char *cmd);
int				execute_builtin(t_shell *sh, t_node *node);
//	execution/execute_external_cmd.c
void			execute_external_cmd(t_shell *sh, t_node *node);
//	execution/path_utils.c
char			*find_cmd_path(char *cmd, char **envp);
//	execution/error_handlers.c
void			handle_cmd_not_found(t_args *args);
void			handle_permission_denied(char *cmd_path, t_args *args);
void			handle_is_directory(char *cmd_path, t_args *args);
void			handle_execve_error(char *cmd_path, t_args *args);
int				is_dir(char *cmd_path);
//	execution/handle_heredoc.
int				handle_heredoc(t_redir *redir, int *new_in);
// execution/pre_process_heredocs.c
int				pre_process_heredocs(t_shell *sh, t_node *node);
//	execution/execution_signals.c
int				set_hd_handler(struct sigaction *old_handler);
int				set_cmd_signals(struct sigaction *old_sa_int);
int				restore_signals(struct sigaction *old_sa_int);
//	execution/expansion_handlers.c
int				handle_expansions(t_shell *sh, t_node *node);
int				handle_redir_expansions(t_shell *sh, t_node *node);
//	execution/convert_cmd_to_array.c
void			handle_array_conversion(t_shell *sh, t_node *node,
					char ***envp, char ***cmd);
//	execution/convert_env_to_array.c
char			**convert_env_list_to_array(t_env *env);
//	utils
void			free_split(char **split);
void			print_error(char *cmd, char *arg, char *error_msg);
void			print_heredoc_error(char *delimiter);
int				parse_error(char *str, t_error *exit_status);
char			*ft_strjoin_quotes(char *s1, char *s2);
size_t			strlen_no_escapes(const char *s);
//	command/utils.c
int				valid_identifier(char *arg, char *command);

/*	***************	*/
/*	PIPE			*/
/*	***************	*/
int				create_pipe(int pipe_fd[2]);
int				create_fork(void);
void			close_fd(int fd);
void			close_pipe(int pipe_fd[2]);
void			safe_dup2(int old_fd, int new_fd);
pid_t			execute_left(t_shell *sh, t_pipe *pipex);
pid_t			execute_right(t_shell *sh, t_pipe *pipex);

//	*********	//
//	EXPANDING	//
//	*********	//
//	expansion/redir/redir_wildcard.c
int				expand_redir_wildcards(t_redir *head);
//	expansion/cmd/cmd_wildcard.c
int				expand_wildcards(t_args *head);
//	expansion/wildcard_main.c
int				process_wildcard_expansion(char *wildcard, char **result);
int				has_wildcard_outside_quotes(char *str);
//	expansion/wildcard_logic.c
int				wildcard_logic(t_pattern *pat, char *s, t_index *i);
int				check_end_pattern(t_pattern *pat);
//	expansion/cmd/cmd_envs.c
int				expand_env(t_shell *sh, t_args *arg);
int				update_arg_value(t_args *arg, char *value);
//	expansion/cmd/cmd_envs_split.c
char			**split_outside_quotes(char *str);
int				split_and_insert(t_args *arg, char **split);
//	expansion_envs_main.c
int				process_string_expansion(t_shell *sh,
					char *file, char **result);
//	expansion/envs_utils.c
int				has_spaces_outside_quotes(char *str);
int				has_env_outside_squotes(char *str);
char			*find_env_value_malloced(t_env *env, char *key);
char			*join_and_free(char *s1, char *s2);
char			*exit_status(t_shell *sh);
//	expansion/redir_envs.c
int				expand_redir_env(t_shell *sh, t_redir *head);
int				handle_redir_word_expansion(t_redir *redir, char *result);
//	expansion/strip_quotes.c
int				strip_quotes_cmd(t_args *head);
int				strip_quotes_redir(t_redir *head);
int				handle_word_expansion(t_args *arg, char *result);

/*	***************	*/
/*	BUILTINS		*/
/*	***************	*/
int				ft_pwd(void);
int				ft_echo(t_args *cmd);
int				ft_env(t_shell *sh);
int				ft_unset(t_shell *sh, t_args *args);
int				ft_export(t_shell *sh, t_args *args);
int				ft_cd(t_shell *sh, t_args *args);
int				ft_exit(t_shell *sh, t_args *args);

#endif
