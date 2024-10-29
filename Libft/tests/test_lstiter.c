/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:45:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 22:40:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	capitalize(void *str)
{
	char	*s;
	int		i;

	s = (char *)str;
	i = 0;
	while (s[i])
	{
		s[i] = ft_toupper(s[i]);
		i++;
	}
}

void	test_lstiter(void)
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
	printf("FT_LSTITER:\n");
	printf("The whole linked list is as follows:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstiter(lst, &capitalize);
	printf("\nAfter lstiter on lst, whole linked list is as follows:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("---------------------------\n\n");
}
