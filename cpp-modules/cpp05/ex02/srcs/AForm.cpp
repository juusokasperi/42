/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:07:52 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/23 18:25:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AForm.hpp"

AForm::AForm(): _name("Default Form"), _gradeToSign(150), _gradeToExecute(150), _isSigned(false)
{
}

AForm::AForm(const std::string name, const int gradeToSign, const int gradeToExecute):
		_name(name), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _isSigned(false)
{
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw (AForm::GradeTooLowException());
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw (AForm::GradeTooHighException());
}

AForm::AForm(const AForm &src): _name(src._name), _gradeToSign(src._gradeToSign),
		_gradeToExecute(src._gradeToExecute), _isSigned(src._isSigned)
{
}

AForm::~AForm()
{
}

const std::string&	AForm::getName() const
{
	return (_name);
}

bool			AForm::getIsSigned() const
{
	return (_isSigned);
}

int			AForm::getGradeToSign() const
{
	return (_gradeToSign);
}

int			AForm::getGradeToExecute() const
{
	return (_gradeToExecute);
}

bool		AForm::isExecutable(const Bureaucrat &executor) const
{
	if (_isSigned == false)
		throw (AForm::FormNotSignedException());
	else if (_gradeToExecute < executor.getGrade())
		throw (AForm::GradeTooLowException());
	return (true);
}

void		AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (_isSigned)
		throw (AForm::FormAlreadySignedException());
	if (bureaucrat.getGrade() > _gradeToSign)
		throw (AForm::GradeTooLowException());
	_isSigned = true;
}

const char	*AForm::GradeTooHighException::what() const noexcept
{
	return ("grade too high");
}

const char	*AForm::GradeTooLowException::what() const noexcept
{
	return ("grade too low");
}

const char	*AForm::FormAlreadySignedException::what() const noexcept
{
	return ("form is already signed");
}

const char	*AForm::FormNotSignedException::what() const noexcept
{
	return ("form is not signed");
}


std::ostream	&operator<<(std::ostream &os, const AForm &form)
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
