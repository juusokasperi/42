/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:01:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:39:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

# define CAT "\033[0;91m[CAT]\033[0m "

class Cat: public Animal {
	private:

	public:
		Cat();
		Cat(const Cat &src);
		Cat& operator=(const Cat &rhs);
		~Cat();

		void	makeSound() const;
};

#endif /* CAT_HPP */
