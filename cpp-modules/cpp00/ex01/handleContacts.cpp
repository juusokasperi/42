/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleContacts.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:42:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/03 17:25:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static std::string	getInput(std::string prompt);
static void			printColumn(std::string str, char c);
static int			printBook(PhoneBook *phoneBook);

void	addContact(PhoneBook *phoneBook)
{
	std::string first;
	std::string last;
	std::string nick;
	std::string phone;
	std::string secret;

	first = getInput("First name:");
	if (first.empty())
		return ;
	last = getInput("Last name:");
	if (last.empty())
		return ;
	nick = getInput("Nickname:");
	if (nick.empty())
		return ;
	phone = getInput("Phone number:");
	if (phone.empty())
		return ;
	secret = getInput("Darkest secret:");
	if (secret.empty())
		return ;
	phoneBook->addContact(first, last, nick, phone, secret);
	std::cout << std::endl;
}

void	searchContact(PhoneBook *phoneBook)
{
	int			i;
	std::string	input;

	i = 0;
	if (printBook(phoneBook) == 0)
		return ;
	std::cout << TMAGENTA << "Enter index (1 - 8): " << TRESET;
	std::getline(std::cin, input);
	if (input.empty() || input.length() > 1)
		std::cout << "Invalid input, back to menu." << std::endl << std::endl;
	else
	{
		try
		{
			i = std::strtol(input.c_str(), NULL, 10);
			if (i < 1 || i > 8)
				throw std::runtime_error("Invalid input, back to menu.");
			phoneBook->printContact(i);
		}
		catch (std::exception &e)
		{
			std::cerr	<< e.what()
						<< std::endl << std::endl;
		}
	}
}

static bool	checkForValidNumber(std::string &input)
{
	size_t	i = 0;
	std::string::size_type	sz;
	if (input[i] == '+')
		i++;
	sz = input.find_first_of("0123456789- ", i);
	if (sz)
		return (false);
	return (true);
}

static std::string getInput(std::string prompt)
{
	std::string input;
	while (1)
	{
		std::cout << std::left << std::setw(16) << prompt;
		std::getline(std::cin, input);
		if (std::cin.eof())
		{
			std::cout << std::endl;
			return ("");
		}
		if (prompt == "Phone number:" && checkForValidNumber(input) == false)
		{
			std::cout << "Phone number can start with a '+', and afterwards contain only digits, ' ' '-'" << std::endl;
			continue;
		}
		if (input.length() > 0)
			break ;
		std::cout << "Input cannot be empty. Try again." << std::endl;
	}
	return (input);
}

static void	printColumn(std::string str, char c)
{
	if (str.length() > 10)
	{
		str.resize(9);
		str.append(".");
	}
	std::cout << std::right << std::setw(10) << str << TYELLOW << c << TRESET;
}

static int	printBook(PhoneBook *phoneBook)
{
	Contact	contact;

	contact = phoneBook->getContact(0);
	if (contact.getFilled() == 0)
	{
		std::cout	<< "Phonebook still empty, back to menu."
					<< std::endl << std::endl;
		return (0);
	}
	printColumn("index", '|');
	printColumn("firstname", '|');
	printColumn("lastname", '|');
	printColumn("nickname", '\n');
	for (int i = 0; i < 8; i++)
	{
		contact = phoneBook->getContact(i);
		if (contact.getFilled() == 0)
			continue ;
		std::string index(1, (i + 1 + '0'));
		printColumn(index, '|');
		printColumn(contact.getFirstName(), '|');
		printColumn(contact.getLastName(), '|');
		printColumn(contact.getNickName(), '\n');
	}
	return (1);
}


