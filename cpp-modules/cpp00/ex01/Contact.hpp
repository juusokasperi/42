/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:20:04 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 13:19:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact {
	private:
		std::string first_;
		std::string last_;
		std::string nick_;
		std::string phone_;
		std::string secret_;
		int			filled;
	public:
		Contact();
		~Contact();
		Contact(std::string firstName, std::string lastName,
			std::string nickName, std::string phone, std::string secret);
		const	std::string& getFirstName() const;
		const	std::string& getLastName() const;
		const	std::string& getNickName() const;
		const	std::string& getPhoneNumber() const;
		const	std::string& getSecret() const;
		int		getFilled() const;
};

#endif
