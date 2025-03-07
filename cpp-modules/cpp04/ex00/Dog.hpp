/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:01:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:21:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

# define DOG "\033[0;94m[DOG]\033[0m "

class Dog: public Animal {
	private:

	public:
		Dog(void);
		Dog(const Dog &src);
		Dog& operator=(const Dog &rhs);
		~Dog(void);

		void	makeSound() const;
};

#endif /* DOG_HPP */
