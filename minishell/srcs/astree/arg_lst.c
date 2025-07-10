/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:37:25 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:42:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*arglst_new(char *arg)
{
	t_args	*new;

	new = (t_args *)ft_calloc(1, sizeof(t_args));
	if (!new)
		return (NULL);
	new->value = ft_strdup(arg);
	if (!new->value)
	{
		ft_free((void **)&new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

int	argadd_back(t_args **lst, t_args *new)
{
	t_args	*last;

	if (!new)
		return (1);
	last = arg_last(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
	return (0);
}

t_args	*arg_last(t_args *lst)
{
	t_args	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
