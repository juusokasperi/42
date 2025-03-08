/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:01:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 01:10:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

# define CAT "\033[0;91m[CAT]\033[0m "

class Cat: public Animal {
	private:
		Brain* _brain;
	public:
		Cat(void);
		Cat(const Cat &src);
		Cat& operator=(const Cat &rhs);
		~Cat(void);

		void	makeSound() const;
		Brain*	getBrain() const;
};

#endif /* CAT_HPP */
