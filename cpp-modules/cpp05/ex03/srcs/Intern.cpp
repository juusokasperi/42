/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:20:34 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 20:32:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &src)
{
	(void)src;
}

Intern& Intern::operator=(const Intern &rhs)
{
	(void)rhs;
	return (*this);
}

Intern::~Intern()
{
}

AForm*	Intern::makePardon(const std::string target) const
{
	return (new PresidentialPardonForm(target));
}

AForm*	Intern::makeShrubbery(const std::string target) const
{
	return (new ShrubberyCreationForm(target));
}

AForm*	Intern::makeRobotomy(const std::string target) const
{
	return (new RobotomyRequestForm(target));
}

AForm*	Intern::makeForm(const std::string name, const std::string target)
{
	AForm* form = NULL;
	FormFunc functions[] = {&Intern::makePardon, &Intern::makeShrubbery,
		&Intern::makeRobotomy};
	std::string	forms[] = { "PARDON", "SHRUBBERY", "ROBOTOMY"};
	for (int i = 0; i < 3; i++)
		if (name == forms[i])
		{
			std::cout << "Intern creates " << name << std::endl;
			form = (this->*functions[i])(target);
		}
	if (!form)
		throw(Intern::WrongFormException());
	return (form);
}

const char	*Intern::WrongFormException::what() const noexcept
{
	return ("invalid form");
}
