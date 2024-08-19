/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 15:41:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	to_linked_list(t_list **list, char *buffer)
{
	t_list *new_node;
	t_list *last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
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

char *fetch_line(t_list *list)
{
	int	str_len;
	char *next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	cpy_str(list, next_str);
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
	cleaned_node = malloc(sizeof(t_list));
	if (!cleaned_node || !buffer)
		return (free(buffer), free(cleaned_node));
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (((char *)last_node->content)[i] && ((char *)last_node->content)[i] != '\n')
		i++;
	while (((char *)last_node->content)[i] && ((char *)last_node->content)[i + 1])
		buffer[j++] = ((char *)last_node->content)[++i];
	buffer[j] = '\0';
	cleaned_node->content = buffer;
	cleaned_node->next = NULL;
	dealloc(list, cleaned_node, buffer);
}

char *get_next_line(int fd)
{
	static t_list	*list[FD_MAX];
	char 			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX - 1)
		return (NULL);
	init_list(&list[fd - 1], fd);
	if (!list[fd - 1])
		return (NULL);
	next_line = fetch_line(list[fd - 1]);
	clean_list(&list[fd - 1]);
	return (next_line);
}
