/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:07:52 by jrinta-           #+#    #+#             */
/*   Updated: 2025/06/05 13:49:49 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Form.hpp"

Form::Form(): _name("Default Form"), _gradeToSign(150), _gradeToExecute(150), _isSigned(false)
{
}

Form::Form(const std::string name, const int gradeToSign, const int gradeToExecute):
		_name(name), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _isSigned(false)
{
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw (Form::GradeTooLowException());
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw (Form::GradeTooHighException());
}

Form::Form(const Form &src): _name(src._name), _gradeToSign(src._gradeToSign),
		_gradeToExecute(src._gradeToExecute), _isSigned(src._isSigned)
{
}

Form::~Form()
{
}

const std::string&	Form::getName() const
{
	return (_name);
}

bool	Form::getIsSigned() const
{
	return (_isSigned);
}

int	Form::getGradeToSign() const
{
	return (_gradeToSign);
}

int	Form::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void	Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw (Form::GradeTooLowException());
	if (_isSigned)
		throw (Form::FormAlreadySignedException());
	_isSigned = true;
}

const char	*Form::FormAlreadySignedException::what() const noexcept
{
	return ("form is already signed");
}

const char	*Form::GradeTooHighException::what() const noexcept
{
	return ("Grade too high");
}

const char	*Form::GradeTooLowException::what() const noexcept
{
	return ("Grade too low");
}

std::ostream	&operator<<(std::ostream &os, const Form &form)
{
	std::string signStatus;

	if (form.getIsSigned())
		signStatus = " is signed";
	else
		signStatus = " is not signed";
	os	<< form.getName() << signStatus << ", grade needed to sign "
		<< form.getGradeToSign() << ", grade needed to execute "
		<< form.getGradeToExecute();
	return (os);
}
