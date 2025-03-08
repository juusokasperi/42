/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:49:37 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:27:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>

# define ANIMAL "\033[95m[Animal]\033[0m "

class Animal {
	protected:
		std::string	_type;
	public:
		Animal();
		Animal(std::string type);
		virtual ~Animal();
		Animal(const Animal &src);
		Animal& operator=(const Animal &rhs);

		virtual void		makeSound() const;
		const std::string	&getType() const;
};

#endif /* ANIMAL_HPP */
