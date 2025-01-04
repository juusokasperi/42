/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:41:25 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/05 01:40:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	ft_isnumber(char *str);
static int	ft_duplicates_overflow(char **values);
static int	ft_validate(char **values);

// Parses all the arguments, works for mixed input.
// After parsing, calls ft_validate
t_stack	*ft_checker_init(int argc, char **argv)
{
	char	**values;
	char	**new_values;
	int		i;
	t_stack	*stack_a;

	values = NULL;
	i = 0;
	while (++i < argc)
	{
		new_values = ft_split(argv[i], ' ');
		if (!new_values || !new_values[0])
			return ((t_stack *)ft_free_split(values, new_values));
		values = ft_join(values, new_values);
		if (!values)
			return (NULL);
	}
	if (!ft_validate(values))
	{
		ft_free_split(values, NULL);
		ft_error_free(NULL, NULL);
	}
	stack_a = ft_checker_parse(values);
	ft_free_split(values, NULL);
	return (stack_a);
}

// Check if all elements in 'values' are integers
static int	ft_validate(char **values)
{
	int		i;

	i = 0;
	while (values[i])
	{
		if (!values[i][0])
			return (0);
		if (!ft_isnumber(values[i]))
			return (0);
		i++;
	}
	if (ft_duplicates_overflow(values))
		return (0);
	return (1);
}

// Check if the values contain only numbers
static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Check for duplicates and integer overflow
static int	ft_duplicates_overflow(char **values)
{
	int			i;
	int			j;
	long long	nbr;

	i = 0;
	while (values[i])
	{
		nbr = ft_atoll(values[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			return (1);
		j = i + 1;
		while (values[j])
		{
			if (nbr == ft_atoll(values[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	**ft_free_split(char **val, char **val_2)
{
	int	i;

	i = 0;
	if (val)
	{
		while (val[i])
			free(val[i++]);
		free(val);
	}
	i = 0;
	if (val_2)
	{
		while (val_2[i])
			free(val_2[i++]);
		free(val_2);
	}
	return (NULL);
}
