/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:03:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/01 17:48:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void	PhoneBook::addContact(std::string first, std::string last,
	std::string nick, std::string phone, std::string secret)
{
	contacts_[index] = Contact(first, last, nick, phone, secret);
	index = (index + 1) % 8;
}

void	printPrompt(std::string prompt, std::string field)
{
	std::cout << std::left << std::setw(18) << prompt;
	std::cout << field << std::endl;
}

void	PhoneBook::printContact(int i)
{
	Contact	contact;

	if (i < 1 || i > 8)
		std::cout << "Error: Index must be a value between 1-8" << std::endl;
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

PhoneBook::~PhoneBook()
{
}

Contact	PhoneBook::getContact(int i)
{
	return (contacts_[i]);
}
