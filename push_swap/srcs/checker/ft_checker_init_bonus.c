/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:41:25 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/05 13:54:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

// Checks that arguments contain only integers
// without any duplicates and that are within the range
// of an integer.

static int	ft_isnumber(char *str);
static int	ft_duplicates_overflow(char **values);
static int	ft_validate(char **values);
static void	ft_free_split(char **values);

t_stack	*ft_checker_init(int argc, char **argv)
{
	char	**values;
	int		values_malloced;
	t_stack	*stack_a;

	values_malloced = 0;
	if (argc == 2)
	{
		values = ft_split(argv[1], ' ');
		if (!values)
			return (NULL);
		values_malloced = 1;
	}
	else
		values = argv + 1;
	if (!ft_validate(values))
	{
		if (values_malloced)
			ft_free_split(values);
		ft_error_free(NULL, NULL);
	}
	stack_a = ft_checker_parse(values);
	if (values_malloced)
		ft_free_split(values);
	return (stack_a);
}

// Check if values are valid
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

static void	ft_free_split(char **values)
{
	int	i;

	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
}
