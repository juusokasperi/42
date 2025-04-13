/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:39:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:41:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << BRAIN << "default constructor called" << std::endl;
}

Brain::Brain(const Brain &src)
{
	std::cout << BRAIN << "copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		_ideas[i] = src._ideas[i];
}

Brain&	Brain::operator=(const Brain &rhs)
{
	std::cout << BRAIN << "copy assignment called" << std::endl;
	if (this != &rhs)
	{
		for (int i = 0; i < 100; i++)
			_ideas[i] = rhs._ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << BRAIN << "destructor called" << std::endl;
}

const std::string&	Brain::getIdea(int i) const
{
	return (_ideas[i]);
}

void	Brain::setIdea(int i, std::string idea)
{
	if (i >= 0 && i < 100)
		_ideas[i] = idea;
}
