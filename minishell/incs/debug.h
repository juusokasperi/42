/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:50:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/14 14:50:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/*	***************	*/
/*		DEBUG		*/
/*	***************	*/
//	debug/debug_print.c
void			print_ast(t_shell *sh, t_node *ast, int depth);
void			print_tokens(t_token *tokens);
//	debug/debug_print_2.c
void			debug_cmd_node(t_shell *sh, t_node *node, int depth);

#endif
