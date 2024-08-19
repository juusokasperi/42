/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:55:36 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 15:44:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		has_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (((char *)list->content)[i] && i < BUFFER_SIZE)
		{
			if (((char *)list->content)[i] == '\n')
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
		while (((char *)list->content)[i])
		{
			if (((char *)list->content)[i] == '\n')
			return (len + 1);
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void cpy_str(t_list *list, char *next_str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (((char *)list->content)[i])
		{
			if (((char *)list->content)[i] == '\n')
			{
				next_str[j] = '\n';
				next_str[j + 1] = '\0';
				return ;
			}
			next_str[j++] = ((char *)list->content)[i++];
		}
		list = list->next;
	}
	next_str[j] = '\0';
}

void	dealloc(t_list **list, t_list *cleaned_node, char *buffer)
{
	t_list *tmp;

	if (!(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (((char *)cleaned_node->content)[0])
		*list = cleaned_node;
	else
	{
		free(buffer);
		free(cleaned_node);
	}
}
