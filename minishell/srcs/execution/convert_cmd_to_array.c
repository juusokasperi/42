/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cmd_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:33:44 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 16:28:29 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_cmd_array(t_args *args, int len);
static int	calculate_cmd_list_len(t_args *args);
static char	**convert_cmd_list_to_array(t_args *args);

void	handle_array_conversion(t_shell *sh, t_node *node,
		char ***envp, char ***cmd)
{
	*envp = NULL;
	*cmd = NULL;
	*envp = convert_env_list_to_array(sh->env);
	if (!*envp)
		return ;
	*cmd = convert_cmd_list_to_array(node->data.command.args);
	if (!*cmd)
		free_split(*envp);
}

static char	**convert_cmd_list_to_array(t_args *args)
{
	int		len;
	char	**cmd;

	len = calculate_cmd_list_len(args);
	cmd = create_cmd_array(args, len);
	if (!cmd)
		return (NULL);
	return (cmd);
}

static char	**create_cmd_array(t_args *args, int len)
{
	char	**cmd;
	int		i;
	t_args	*temp;

	cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	temp = args;
	i = 0;
	while (temp)
	{
		cmd[i] = ft_strdup(temp->value);
		if (!cmd[i])
		{
			while (--i >= 0)
				ft_free((void **)&cmd[i]);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

static int	calculate_cmd_list_len(t_args *args)
{
	int		len;
	t_args	*temp;

	temp = args;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
