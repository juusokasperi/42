/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:32:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 11:47:30 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	printStr(char *s)
{
	while (*s)
	{
		std::cout << (char)std::toupper(*s);
		s++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		argv++;
		while (*argv)
		{
			printStr(*argv);
			argv++;
		}
	}
	std::cout << std::endl;
	return (0);
}
