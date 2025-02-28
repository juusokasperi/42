/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:44:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/28 15:57:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>

class PhoneBook {
	private:
		std::string name;
		int			val;
	public:
		SimpleClass(std::string name, int val);
		~SimpleClass();
		void		print();
};

#endif /* PHONEBOOK_HPP */
