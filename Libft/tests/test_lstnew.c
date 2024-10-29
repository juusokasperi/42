/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:37:11 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 22:11:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstnew(void)
{
	t_list *lst;

	printf("---------------------------\n");
	printf("FT_LSTNEW:\n");
	lst = ft_lstnew(strdup("This is a linked list."));
	printf("Lst content is \"%s\"\n", (char *)lst->content);
	ft_lstdelone(lst, free);
	printf("---------------------------\n\n");
}
