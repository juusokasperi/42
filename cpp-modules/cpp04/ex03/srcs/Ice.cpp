/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:51:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 16:42:36 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(): AMateria("ice")
{
	std::cout << ICE << "constructor called" << std::endl;
}

Ice::Ice(const Ice &src): AMateria(src)
{
	std::cout << ICE << "copy constructor called" << std::endl;
}

Ice&	Ice::operator=(const Ice &rhs)
{
	std::cout << ICE << "copy assignment called" << std::endl;
	if (this != &rhs)
		AMateria::operator=(rhs);
	return (*this);
}

Ice::~Ice()
{
	std::cout << ICE << "destructor called" << std::endl;
}

AMateria*	Ice::clone() const
{
	return (new Ice(*this));
}

void	Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
