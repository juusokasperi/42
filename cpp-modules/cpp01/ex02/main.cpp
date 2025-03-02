/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:16:19 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 16:28:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <iomanip>

int	main(void)
{
	std::string		string = "HI THIS IS BRAIN";
	std::string*	stringPTR = &string;
	std::string&	stringREF = string;

	std::cout << std::setfill('.') << std::setw(9) << std::right
	<< "string" << ":" << &string
	<< ":" << string << std::endl;
	std::cout << std::setw(9) << std::left << "stringPTR" << ":" << stringPTR
	<< ":" << *stringPTR << std::endl;
	std::cout << std::setw(9) << std::left << "stringREF" << ":" << &stringREF
	<< ":" << stringREF << std::endl;
}
