/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:38:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 00:11:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

static void	printStatus();

int	main()
{
	std::string	input;
	PhoneBook	phoneBook;

	printStatus();
	while (42)
	{
		std::cout << TMAGENTA << "Enter command:  " << TRESET;
		if (!(std::getline(std::cin, input)))
			return (1);
		if (input.compare("ADD") == 0)
			addContact(&phoneBook);
		else if (input.compare("SEARCH") == 0)
			searchContact(&phoneBook);
		else if (input.compare("EXIT") == 0)
			break ;
		else
		{
			std::cout << "Invalid input, try again." << std::endl;
			continue ;
		}
		if (std::cin.eof())
			break ;
		printStatus();
	}
	return (0);
}

static void	printStatus()
{
	std::cout	<< TYELLOW
				<< "Type ADD to save a new contact, "
				<< "SEARCH to search for contacts, "
				<< "EXIT to quit the book"
				<< std::endl << std::endl << TRESET;
}
