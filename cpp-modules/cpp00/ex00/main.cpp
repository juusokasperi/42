/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:32:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/28 14:55:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	print_arg(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (std::isalpha(string[i]))
			std::cout << (char)std::toupper(string[i]);
		else
			std::cout << (char)string[i];
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		argv++;
		while (*argv != NULL)
		{
			print_arg(*argv);
			argv++;
		}
	}
	std::cout << std::endl;
	return (0);
}
