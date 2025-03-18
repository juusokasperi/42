/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:50:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 15:31:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	try {
		std::cout << "Building a form with incorrect grades 151" << std::endl;
		Form paper("Paper", 151, 151);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a form with incorrect grades 0" << std::endl;
		Form paper("Paper", 0, 0);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a form with correct grades" << std::endl;
		Form paper("Paper", 50, 10);
		std::cout << paper << std::endl;
		Bureaucrat bill("Bill", 1);
		std::cout << bill << std::endl;
		bill.signForm(paper);
		std::cout << paper << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "Building a bureaucrat with grade 150" << std::endl;
		Bureaucrat jim("Jim", 150);
		std::cout << jim << std::endl;
		Form paper("Paper", 50, 10);
		std::cout << paper << std::endl;
		jim.signForm(paper);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
