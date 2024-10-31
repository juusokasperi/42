/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:37:11 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 12:15:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstnew(void)
{
	t_list	*lst;
	t_list	*current;

	printf("---------------------------\n");
	printf("FT_LSTNEW:\n");
	lst = ft_lstnew(strdup("This is a linked list w/ one element."));
	current = lst;
	printf("List content is:\n");
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
		ft_lstdelone(lst, free);
	printf("---------------------------\n\n");
}
