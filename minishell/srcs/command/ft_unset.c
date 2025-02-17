/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:53:46 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 18:16:30 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_handler(t_shell *sh, t_args *tmp);
static void	remove_env(t_shell *sh, t_env **env, t_env **prev);

int	ft_unset(t_shell *sh, t_args *args)
{
	t_args	*tmp;
	bool	err;

	if (!sh || !args || !args->next || !args->next->value)
		return (EXIT_SUCCESS);
	tmp = args->next;
	err = false;
	while (tmp)
	{
		if (!valid_identifier(tmp->value, "unset"))
			err = true;
		else
			ft_unset_handler(sh, tmp);
		tmp = tmp->next;
	}
	if (err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	ft_unset_handler(t_shell *sh, t_args *tmp)
{
	t_env	*env;
	t_env	*prev;

	env = sh->env;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, tmp->value) == 0)
			remove_env(sh, &env, &prev);
		else
		{
			prev = env;
			env = env->next;
		}
	}
}

static void	remove_env(t_shell *sh, t_env **env, t_env **prev)
{
	if (*prev)
		(*prev)->next = (*env)->next;
	else
		sh->env = (*env)->next;
	ft_free((void **)&((*env)->key));
	ft_free((void **)&((*env)->value));
	ft_free((void **)env);
	if (*prev)
		*env = (*prev)->next;
	else
		*env = sh->env;
}
