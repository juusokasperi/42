/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:38:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/03 16:29:27 by jrinta-          ###   ########.fr       */
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
		if (input == "ADD")
			addContact(&phoneBook);
		else if (input == "SEARCH")
			searchContact(&phoneBook);
		else if (input == "EXIT")
			break ;
		else
		{
			std::cout << "Invalid input, try again." << std::endl;
			continue ;
		}
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
