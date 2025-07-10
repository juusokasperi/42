/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:01:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:43:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

# define DOG "\033[0;94m[DOG]\033[0m "

class Dog: public AAnimal {
	private:
		Brain* _brain;
	public:
		Dog();
		Dog(const Dog &src);
		Dog& operator=(const Dog &rhs);
		~Dog();

		void	makeSound() const;
		Brain*	getBrain()	const;
};

#endif /* DOG_HPP */
