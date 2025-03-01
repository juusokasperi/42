/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:36:15 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/01 17:28:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Contact.hpp"

Contact::Contact()
{
	first_ = "";
	last_ = "";
	nick_ = "";
	phone_ = "";
	secret_ = "";
	filled = 0;
}

Contact::Contact(std::string first_name, std::string last_name,
	std::string nick_name, std::string phone, std::string secret)
{
	first_ = first_name;
	last_ = last_name;
	nick_ = nick_name;
	phone_ = phone;
	secret_ = secret;
	filled = 1;
}

Contact::~Contact()
{
}

const std::string&	Contact::getFirstName() const
{
	return (first_);
}

const std::string&	Contact::getLastName() const
{
	return (last_);
}

const std::string&	Contact::getNickName() const
{
	return (nick_);
}

const std::string&	Contact::getPhoneNumber() const
{
	return (phone_);
}

const std::string&	Contact::getSecret() const
{
	return (secret_);
}

int	Contact::getFilled() const
{
	return (filled);
};
