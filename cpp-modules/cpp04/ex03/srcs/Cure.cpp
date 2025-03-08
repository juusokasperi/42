/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:51:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 12:56:25 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(): AMateria("cure")
{
	std::cout << CURE << "constructor called" << std::endl;
}

Cure::Cure(const Cure &src): AMateria(src)
{
	std::cout << CURE << "copy constructor called" << std::endl;
}

Cure&	Cure::operator=(const Cure &rhs)
{
	std::cout << CURE << "copy assignment called" << std::endl;
	if (this != &rhs)
		AMateria::operator=(rhs);
	return (*this);
}

Cure::~Cure()
{
	std::cout << CURE << "destructor called" << std::endl;
}

AMateria*	Cure::clone() const
{
	return (new Cure(*this));
}

void	Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
