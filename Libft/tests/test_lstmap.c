/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:45:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 23:18:25 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	*capitalize(void *str)
{
	char	*s;
	char	*new_str;
	int		i;

	s = (char *)str;
	new_str = strdup(s);
	if (!new_str)
		return (NULL);
	i = 0;
	while (new_str[i])
	{
		new_str[i] = ft_toupper(new_str[i]);
		i++;
	}
	return (new_str);
}

void	test_lstmap(void)
{
	t_list *lst;
	t_list *lst2;
	t_list *lst3;
	t_list *new_lst;
	t_list *current;

	lst = ft_lstnew(strdup("First element."));
	lst2 = ft_lstnew(strdup("Second element."));
	lst3 = ft_lstnew(strdup("Third element."));
	new_lst = NULL;
	ft_lstadd_back(&lst, lst2);
	ft_lstadd_back(&lst, lst3);
	printf("---------------------------\n");
	printf("FT_LSTMAP:\n");
	printf("The whole linked list is as follows:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("\nAfter lstmap on lst, new linked list is as follows:\n");
	new_lst = ft_lstmap(lst, capitalize, free);
	current = new_lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("\nAnd old list is still:\n");
	current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&lst, free);
	ft_lstclear(&new_lst, free);
	printf("---------------------------\n\n");
}
