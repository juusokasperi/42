/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:53:57 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/28 15:54:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simpleClass.hpp"

SimpleClass::SimpleClass(std::string name, int val): name(name), val(val)
{
	std::cout << "Constructing simple object" << std::endl;
}

SimpleClass::~SimpleClass()
{
	std::cout << "Destructing simple object" << std::endl;
}

void	SimpleClass::print()
{
	std::cout << "Name " << this->name << std::endl;
	std::cout << "Val " << this->val << std::endl;
}
