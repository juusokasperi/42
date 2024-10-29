/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:45:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 22:33:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstdelone(void)
{
	t_list *lst;
	t_list *lst2;
	t_list *lst3;
	t_list *current;

	lst = ft_lstnew(strdup("First element."));
	lst2 = ft_lstnew(strdup("Second element."));
	lst3 = ft_lstnew(strdup("Third element."));
	ft_lstadd_back(&lst, lst2);
	ft_lstadd_back(&lst, lst3);
	printf("---------------------------\n");
	printf("FT_LSTDELONE:\n");
	printf("The whole linked list is as follows:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstdelone(lst3, free);
	lst2->next = NULL;
	printf("\nAfter lstdelone on lst3, whole linked list is as follows:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("---------------------------\n\n");
}
