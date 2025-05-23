/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:57:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/23 18:30:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("Shrubbery Creation Form", 145, 137), _target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("Shrubbery Creation Form", 145, 137), _target(target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src): AForm("Shrubbery Creation Form", 145, 137), _target(src._target)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs)
{
	if (this != &rhs)
		_target = rhs._target;
	return (*this);
}

void	ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	if (!isExecutable(executor))
		throw (AForm::GradeTooLowException());
	std::ofstream outFile(_target + "_shrubbery");
	if (!outFile)
	{
		std::cerr << "Error: " << "Could not create the shrubbery file." << std::endl;
		return ;
	}
	outFile <<
		"    ccc8808o     \n"
		"  cC8080808Po0b  \n"
		"  c008080UOpugbD \n"
		"    d08Be8gggUC  \n"
		" CgggbU8OU q0pDc \n"
		"    60OU   \\p G  \n"
		"     \\\\//  /doU \n"
		"      \\\\//////  \n"
		"       |||/\\/   \n"
		"       |||\\/    \n"
		"       |||||     \n"
		".....//|||||\\...\n";
	outFile.close();
	std::cout << "Shrubbery file created: " << _target + "_shrubbery" << std::endl;
	}
