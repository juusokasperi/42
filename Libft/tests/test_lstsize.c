/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:15:00 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 22:20:26 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lstsize(void)
{
	t_list *lst;
	t_list *lst2;
	t_list *lst3;

	lst = ft_lstnew(strdup("First element."));
	lst2 = ft_lstnew(strdup("Seconde element."));
	lst3 = ft_lstnew(strdup("Third element."));
	ft_lstadd_back(&lst, lst2);
	ft_lstadd_back(&lst, lst3);
	printf("---------------------------\n");
	printf("FT_LSTSIZE:\n");
	printf("Size of lst (has 3 elements) is: %i\n", ft_lstsize(lst));
	printf("---------------------------\n\n");
	ft_lstclear(&lst, free);
}
