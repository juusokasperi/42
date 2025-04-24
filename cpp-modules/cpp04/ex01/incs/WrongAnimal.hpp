/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:49:37 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:22:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>

# define WRONGANIMAL "\033[95m[WrongAnimal]\033[0m "

class WrongAnimal {
	protected:
		std::string	_type;
	public:
		WrongAnimal();
		WrongAnimal(std::string type);
		~WrongAnimal();
		WrongAnimal(const WrongAnimal &src);
		WrongAnimal& operator=(const WrongAnimal &rhs);

		void		makeSound() const;
		const std::string	&getType() const;
};

#endif /* WRONGANIMAL_HPP */
