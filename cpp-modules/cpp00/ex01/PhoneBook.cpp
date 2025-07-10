/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:03:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/03 16:48:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void	PhoneBook::addContact(std::string first, std::string last,
	std::string nick, std::string phone, std::string secret)
{
	contacts_[index] = Contact(first, last, nick, phone, secret);
	index = (index + 1) % 8;
}

PhoneBook::PhoneBook()
{
	index = 0;
}

PhoneBook::~PhoneBook()
{
}

static void	printPrompt(std::string prompt, std::string field)
{
	std::cout << std::left << std::setw(18) << prompt;
	std::cout << field << std::endl;
}

void	PhoneBook::printContact(int i) const
{
	Contact	contact;

	if (i < 1 || i > 8)
		std::cerr << "Error: Index must be a value between 1-8" << std::endl;
	else
	{
		i--;
		contact = contacts_[i];
		if (contact.getFilled())
		{
			printPrompt("First name: ", contact.getFirstName());
			printPrompt("Last name: ", contact.getLastName());
			printPrompt("Nickname: ", contact.getNickName());
			printPrompt("Phone number: ", contact.getPhoneNumber());
			printPrompt("Darkest secret: ", contact.getSecret());
		}
		else
		{
			std::cout << "Contact is not yet filled. Returning to main menu.";
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

Contact	PhoneBook::getContact(int i) const
{
	return (contacts_[i]);
}
