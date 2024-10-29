/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstaddback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:45:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 22:28:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstaddback(void)
{
	t_list *lst;
	t_list *lst2;
	t_list *current;

	printf("---------------------------\n");
	printf("FT_LSTADDBACK:\n");
	lst = ft_lstnew(strdup("This is a linked list element."));
	lst2 = ft_lstnew(strdup("Second element to linked list."));
	ft_lstadd_back(&lst, lst2);
	printf("After adding lst2 to back the linked list is:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&lst, free);
	printf("---------------------------\n\n");
}
