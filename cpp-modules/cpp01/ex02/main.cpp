/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:16:19 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 22:57:25 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>

#define TYELLOW	"\033[0;93m"
#define TRESET	"\033[0;0m"
#define SPACER 	"\033[0;93m:\033[0;0m"

int	main(void)
{
	std::string		string = "HI THIS IS BRAIN";
	std::string*	stringPTR = &string;
	std::string&	stringREF = string;

	std::cout << std::setfill('.') << std::setw(9) << "name" << SPACER
	<< std::setw(11) << "address" << SPACER << std::setw(16) << "value" << std::endl;
	std::cout << std::setfill('.') << std::setw(9) << std::right
	<< "string" << SPACER << &string
	<< SPACER << string << std::endl;
	std::cout << std::setw(9) << std::left << "stringPTR" << SPACER << stringPTR
	<< SPACER << *stringPTR << std::endl;
	std::cout << std::setw(9) << std::left << "stringREF" << SPACER << &stringREF
	<< SPACER << stringREF << std::endl;
}
