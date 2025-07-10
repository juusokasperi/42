/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:50:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/06/05 13:46:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	try {
		std::cout << "Building a form with incorrect grades 151\n";
		Form paper("Paper", 151, 151);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	try {
		std::cout << "\nBuilding a form with incorrect grades 0\n";
		Form paper("Paper", 0, 0);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	try {
		Bureaucrat bill("Bill", 1);
		std::cout << "\nBuilt a ";
		std::cout << bill << "\n";
		Form paper("Paper", 50, 10);
		std::cout << paper << "\n";
		bill.signForm(paper);
		std::cout << paper << "\n";
        bill.signForm(paper);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	try {
		Bureaucrat jim("Jim", 150);
		std::cout << "\nBuilt a ";
		std::cout << jim << "\n";
		Form paper("Paper", 50, 10);
		std::cout << paper << "\n";
		jim.signForm(paper);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	return (0);
}
