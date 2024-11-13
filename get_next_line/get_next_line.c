/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/13 17:34:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	to_linked_list(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buffer;
	new_node->next = NULL;
}

void	init_list(t_list **list, int fd)
{
	int		chars_read;
	char	*buffer;

	while (!has_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (!chars_read)
		{
			free(buffer);
			return ;
		}
		buffer[chars_read] = '\0';
		to_linked_list(list, buffer);
	}
}

char	*fetch_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	clean_list(t_list **list)
{
	t_list	*last_node;
	t_list	*cleaned_node;
	int		i;
	int		j;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	cleaned_node = malloc(sizeof(t_list));
	if (!cleaned_node)
		return (free(buffer));
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[i + 1])
		buffer[j++] = last_node->str_buf[++i];
	buffer[j] = '\0';
	cleaned_node->str_buf = buffer;
	cleaned_node->next = NULL;
	dealloc(list, cleaned_node, buffer);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0
		|| read(fd, 0, 0) < 0)
		return (NULL);
	init_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = fetch_line(list);
	clean_list(&list);
	return (next_line);
}
