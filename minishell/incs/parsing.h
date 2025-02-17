/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:50:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/14 14:50:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*	*****	*/
/*	LEXER	*/
/*	*****	*/
//	lexer/lex.c
void			lexer(t_lexer *lex);
//	lexer/handlers.c
void			handle_pipe_or(t_lexer *lex, t_error *exit_s);
void			handle_redir(t_lexer *lex, t_error *exit_s);
void			handle_and(t_lexer *lex, t_error *exit_s);
//	lexer/handlers_2.c
void			handle_parentheses(t_lexer *lex, t_error *exit_s);
void			handle_word(t_lexer *lex, t_error *exit_s);
//	lexer/lst_tools.c
void			free_token_list(t_token **lst);
t_token			*tokenlst_new(t_token_type type, char *value);
t_token			*token_last(t_token *lst);
int				tokenadd_back(t_token **lst, t_token *new);
//	lexer/check_syntax.c
int				check_syntax(t_lexer *lex);

/*	***************	*/
/*	PARSER / ASTREE	*/
/*	***************	*/
//	astree/create_ast.c
t_node			*create_ast(t_token **tokens, t_error *lex_error);
t_node			*create_binary_node(t_node_type type, char *op);
t_node			*create_subsh_node(t_node *subsh);
t_node			*create_cmd_node(void);
//	astree/node_tools.c
t_node			*handle_pipe_and_or(t_token **tokens);
t_node			*parse_parentheses(t_token **tokens);
void			consume_token(t_token **tokens);
int				is_redir_token(t_token_type type);
//	astree/parse.c
t_node			*parse_expressions(t_token **tokens);
t_node			*parse_pipe(t_token **tokens);
t_node			*parse_simple_cmd(t_token **tokens);
//	astree/parse_redir_cmd.c
t_node			*parse_redir_or_cmd(t_token **tokens);
//	astree_parse_redir_cmd_utils.c
int				rediradd_back(t_redir **redir, t_token_type type, char *str);
t_redir			*redirlst_new(t_token_type type, char *str);
//	astree/free_ast.c
t_node			*free_ast(t_node *node);
void			free_args(t_args *arg);
void			free_redirs(t_redir *redir);
void			free_cmd_node(t_node *node);
void			free_binary_node(t_node *node);
//	astree/arg_lst.c
t_args			*arg_last(t_args *lst);
t_args			*arglst_new(char *arg);
int				argadd_back(t_args **lst, t_args *new);

#endif
