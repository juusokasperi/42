/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:43:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 16:39:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(std::string const &type): _type(type)
{
	std::cout << AMATERIA << "type " << _type << " created." << std::endl;
}

AMateria::AMateria(const AMateria &src): _type(src._type)
{
	std::cout << AMATERIA << _type << " copy constructor called" << std::endl;
}

AMateria&	AMateria::operator=(const AMateria &rhs)
{
	std::cout << AMATERIA << "copy assignment called" << std::endl;
	if (this != &rhs)
		_type = rhs._type;
	return (*this);
}

AMateria::~AMateria()
{
	std::cout << AMATERIA << "destructor called" << std::endl;
}

const std::string&	AMateria::getType() const
{
	return (_type);
}
