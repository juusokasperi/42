/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:50:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 17:12:22 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

static void	executeShrubbery(void);
static void	executeRobotomy(void);
static void	executePardon(void);

int	main(void)
{
	executeShrubbery();
	executeRobotomy();
	executePardon();
	return (0);
}

static void	executePardon(void)
{
	std::cout << "\033[0;92m----- PARDON TESTS -----\033[0m" << std::endl;
	try {
		std::cout << "Building a pardon form" << std::endl;
		PresidentialPardonForm pardon("Joe the Third");
		Bureaucrat bill("Bill", 1);
		bill.executeForm(pardon);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a pardon form" << std::endl;
		PresidentialPardonForm pardon("Joe the Third");
		Bureaucrat bill("Bill", 1);
		bill.signForm(pardon);
		bill.executeForm(pardon);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a pardon form" << std::endl;
		PresidentialPardonForm pardon("Joe the Third");
		Bureaucrat bill("Bill", 25);
		bill.signForm(pardon);
		bill.executeForm(pardon);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

static void	executeRobotomy(void)
{
	std::cout << "\033[0;92m-----  ROBO TESTS  -----\033[0m" << std::endl;
	srand(time(NULL));
	try {
		std::cout << "Building a robotomy form" << std::endl;
		RobotomyRequestForm robo("robo");
		Bureaucrat bill("Bill", 1);
		bill.executeForm(robo);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a robotomy form" << std::endl;
		RobotomyRequestForm robo("Old McDonald");
		Bureaucrat bill("Bill", 1);
		bill.signForm(robo);
		bill.executeForm(robo);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a robotomy form" << std::endl;
		RobotomyRequestForm robo("robo");
		Bureaucrat bill("Bill", 72);
		bill.signForm(robo);
		bill.executeForm(robo);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

static void	executeShrubbery(void)
{
	std::cout << "\033[0;92m----- SHRUB  TESTS -----\033[0m" << std::endl;
	try {
		std::cout << "Building a shrubbery form" << std::endl;
		ShrubberyCreationForm shrub("plant");
		Bureaucrat bill("Bill", 1);
		bill.executeForm(shrub);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a shrubbery form" << std::endl;
		ShrubberyCreationForm shrub("plant");
		Bureaucrat bill("Bill", 1);
		bill.signForm(shrub);
		bill.executeForm(shrub);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a shrubbery form" << std::endl;
		ShrubberyCreationForm shrub("plant");
		Bureaucrat bill("Bill", 145);
		bill.signForm(shrub);
		bill.executeForm(shrub);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}
