/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:38:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/01 17:47:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

static void	print_status();

int	main()
{
	std::string	input;
	PhoneBook	phoneBook;

	print_status();
	while (42)
	{
		std::cout << TMAGENTA << "Enter command:  " << TRESET;
		if (!(std::getline(std::cin, input)))
			return (1);
		if (input.compare("ADD") == 0)
			add_contact(&phoneBook);
		else if (input.compare("SEARCH") == 0)
			search_contact(&phoneBook);
		else if (input.compare("EXIT") == 0)
			break ;
		else
		{
			std::cout << "Invalid input, try again." << std::endl;
			continue ;
		}
		if (std::cin.eof())
			break ;
		print_status();
	}
	return (0);
}

static void	print_status()
{
	std::cout << TYELLOW << "Type ADD to save a new contact, " <<
	"SEARCH to search for contacts, " << "EXIT to quit the book"
	<< std::endl << std::endl << TRESET;
}
