/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:55:36 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/13 17:35:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_list *list, char *next_str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				next_str[j] = '\n';
				next_str[j + 1] = '\0';
				return ;
			}
			next_str[j++] = list->str_buf[i++];
		}
		list = list->next;
	}
	next_str[j] = '\0';
}

void	dealloc(t_list **list, t_list *cleaned_node, char *buffer)
{
	t_list	*tmp;

	if (!(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (cleaned_node->str_buf[0])
		*list = cleaned_node;
	else
	{
		free(buffer);
		free(cleaned_node);
	}
}
