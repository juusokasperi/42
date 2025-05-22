/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:19:54 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/02 12:08:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): _name("Default Bureaucrat"), _grade(150)
{
}

Bureaucrat::Bureaucrat(const std::string name, int grade): _name(name), _grade(grade)
{
	if (grade < 1)
		throw (Bureaucrat::GradeTooHighException());
	if (grade > 150)
		throw (Bureaucrat::GradeTooLowException());
}

Bureaucrat::Bureaucrat(const Bureaucrat &src): _name(src._name), _grade(src._grade)
{
}

Bureaucrat::~Bureaucrat()
{
}

const char	*Bureaucrat::GradeTooHighException::what() const noexcept
{
	return ("Grade too high");
}

const char	*Bureaucrat::GradeTooLowException::what() const noexcept
{
	return ("Grade too low");
}

const std::string&	Bureaucrat::getName() const
{
	return (_name);
}

void		Bureaucrat::signForm(Form &form) const
{
	try {
		form.beSigned(*this);
		std::cout << *(this) << ", signed " << form.getName() << std::endl;;
	}
	catch (std::exception &e) {
		std::cout << *this << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
	}
}

int			Bureaucrat::getGrade() const
{
	return (_grade);
}

void	Bureaucrat::incrementGrade()
{
	if (_grade == 1)
		throw (Bureaucrat::GradeTooHighException());
	_grade -= 1;
}

void	Bureaucrat::decrementGrade()
{
	if (_grade == 150)
		throw (Bureaucrat::GradeTooLowException());
	_grade += 1;
}

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &bureaucrat)
{
	os	<< bureaucrat.getName() << ", bureaucrat grade "
		<< bureaucrat.getGrade();
	return (os);
}
