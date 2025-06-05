/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:50:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/06/05 13:24:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	try {
		std::cout << "Building a bureaucrat with grade -150" << std::endl;
		Bureaucrat joe("Joe", -150);
		std::cout << joe << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "\nBuilding a bureaucrat with grade 1" << std::endl;
		Bureaucrat bill("Bill", 1);
		std::cout << bill << std::endl;
		std::cout << "Trying to increment" << std::endl;
		bill.incrementGrade();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "\nBuilding a bureaucrat with grade 150" << std::endl;
		Bureaucrat jim("Jim", 150);
		std::cout << jim << std::endl;
		std::cout << "Trying to decrement" << std::endl;
		jim.decrementGrade();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "\nBuilding a bureaucrat with grade 1" << std::endl;
		Bureaucrat bill("Bill", 1);
		std::cout << bill << std::endl;
		std::cout << "Trying to decrement" << std::endl;
		bill.decrementGrade();
		std::cout << bill << std::endl;
		std::cout << "Trying to increment" << std::endl;
		bill.incrementGrade();
		std::cout << bill << std::endl;
		std::cout << "Trying to increment again" << std::endl;
		bill.incrementGrade();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
