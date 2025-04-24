/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:01:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:27:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

# define WRONGCAT "\033[0;91m[WRONGCAT]\033[0m "

class WrongCat: public WrongAnimal {
	private:

	public:
		WrongCat(void);
		WrongCat(const WrongCat &src);
		WrongCat& operator=(const WrongCat &rhs);
		~WrongCat(void);

		void	makeSound() const;
};

#endif /* WRONGCAT_HPP */
