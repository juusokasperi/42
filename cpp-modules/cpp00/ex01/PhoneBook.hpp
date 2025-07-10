/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:44:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/03 16:59:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <iomanip>
# include "Contact.hpp"

# ifndef TMAGENT
#  define TMAGENTA "\033[95m"
# endif
# ifndef TRESET
#  define TRESET "\033[0m"
# endif

class PhoneBook {
	private:
		Contact	contacts_[8];
		int		index;
	public:
		PhoneBook();
		~PhoneBook();
		void	addContact(std::string first, std::string last,
			std::string nick, std::string phone, std::string secret);
		void	printContact(int i) const;
		Contact getContact(int i) const;
};

#endif /* PHONEBOOK_HPP */
