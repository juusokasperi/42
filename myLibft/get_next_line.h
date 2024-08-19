/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:22:08 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 15:36:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
#ifndef FD_MAX
# define FD_MAX 1024
#endif

# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"
# include "stdio.h"

char 	*get_next_line(int fd);
int		has_newline(t_list *list);
t_list	*find_last_node(t_list *list);
int		len_to_newline(t_list *list);
void	dealloc(t_list **list, t_list *cleaned_node, char *buffer);
void 	cpy_str(t_list *list, char *next_str);

#endif
