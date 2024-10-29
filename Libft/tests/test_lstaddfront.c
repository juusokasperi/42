/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstaddfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:45:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 22:22:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstaddfront(void)
{
	t_list *lst;
	t_list *lst2;
	t_list *current;

	printf("---------------------------\n");
	printf("FT_LSTADDFRONT:\n");
	lst = ft_lstnew(strdup("This is a linked list element."));
	lst2 = ft_lstnew(strdup("New element to linked list"));
	printf("Before: lst is \"%s\" and lst2 is \"%s\"\n\n",
		(char *)lst->content, (char *)lst2->content);
	ft_lstadd_front(&lst, lst2);
	printf("After adding lst2 to front the linked list is:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&lst, free);
	printf("---------------------------\n\n");
}
