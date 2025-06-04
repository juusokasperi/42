/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:57:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 16:31:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("Robotomy Request Form", 72, 45), _target("Some Random Chump")
{
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): AForm("Robotomy Request Form", 72, 45), _target(target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src): AForm("Robotomy Request Form", 72, 45), _target(src._target)
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &rhs)
{
	if (this != &rhs)
		_target = rhs._target;
	return (*this);
}

void	RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
	if (!isExecutable(executor))
		throw (AForm::GradeTooLowException());
	std::cout << "\033[0;93mDRRRR... DRRRR... *drilling noises*\033[0m" << std::endl;
	bool	success = rand() % 2 != 0;
	if (success)
		std::cout << _target << " has been \033[0;92msuccesfully\033[0m robotomized!" << std::endl;
	else
		std::cout << _target << "'s robotomy was a \033[0;91mfailure\033[0m." << std::endl;
}
