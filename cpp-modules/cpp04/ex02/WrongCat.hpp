/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:01:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:43:32 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

# define WRONGCAT "\033[0;91m[WRONGCAT]\033[0m "

class WrongCat: public WrongAnimal {
	private:

	public:
		WrongCat();
		WrongCat(const WrongCat &src);
		WrongCat& operator=(const WrongCat &rhs);
		~WrongCat();

		void	makeSound() const;
};

#endif /* WRONGCAT_HPP */
