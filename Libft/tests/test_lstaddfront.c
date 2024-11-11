/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstaddfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:45:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/09 13:10:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstaddfront(void)
{
	t_list	*lst;
	t_list	*lst2;
	t_list	*lst3;
	t_list	*current;

	printf("---------------------------\n");
	printf("FT_LSTADDFRONT:\n");
	lst = ft_lstnew(strdup("This was originally the first linked list element."));
	lst2 = ft_lstnew(strdup("New element to linked list"));
	lst3 = ft_lstnew(strdup("Third element to linked list"));
	ft_lstadd_front(&lst, lst2);
	ft_lstadd_front(&lst, lst3);
	lst3 = ft_lstlast(lst);
	printf("After adding lst2 & lst3 to front the linked list is:\n");
	current = lst;
	printf("Lst: %p\n", lst);
	printf("Lst2: %p\n", lst2);
	printf("Lst3: %p\n", lst3);
	while (current)
	{
		printf("%p\n", current);
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&lst, free);
	lst2 = ft_lstnew(strdup("This element was added to front of a null list"));
	ft_lstadd_front(&lst, lst2);
	printf("\nAfter adding lst2 to front of empty list is:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&lst, free);
	printf("---------------------------\n\n");
}
