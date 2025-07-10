/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:58:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/05 21:00:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_free((void **)&((*lst)->value));
		ft_free((void **)lst);
		*lst = temp;
	}
	*lst = NULL;
}

t_token	*tokenlst_new(t_token_type type, char *value)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		ft_free((void **)&new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*token_last(t_token *lst)
{
	t_token	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

int	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return (1);
	last = token_last(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
	return (0);
}
