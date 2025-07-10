/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:49:37 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 01:09:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>

# define AANIMAL "\033[95m[AAnimal]\033[0m "

class AAnimal {
	protected:
		std::string	_type;
	public:
		AAnimal();
		AAnimal(std::string type);
		virtual ~AAnimal();
		AAnimal(const AAnimal &src);
		AAnimal& operator=(const AAnimal &rhs);

		virtual void		makeSound() const = 0;
		const std::string	&getType() const;
};

#endif /* AANIMAL_HPP */
