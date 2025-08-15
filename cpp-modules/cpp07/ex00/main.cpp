/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:17:52 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/15 19:25:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"
#include <iostream>

int	main(void)
{
	int a = 2;
	int b = 3;

	std::cout << "---- Before swap: ----\n";
	std::cout << "a = " << a << ", b = " << b << "\n";
	swap(a, b);
	
	std::cout << "---- After swap: ----\n";
	std::cout << "a = " << a << ", b = " << b << "\n\n";
	
	std::cout << "min(" << a << ", " << b << ") = " << ::min( a, b ) << "\n";
	std::cout << "max(" << a << ", " << b << ") = " << ::max( a, b ) << "\n\n";
		
	std::string c = "string1";
	std::string d = "string2";
	
	std::cout << "---- Before swap: ----\n";
	std::cout << "c = " << c << ", d = " << d << "\n";
	swap(c, d);
	std::cout << "---- After swap: ----\n";
	std::cout << "c = " << c << ", d = " << d << "\n\n";

	std::cout << "min( " << c << ", " << d << ") = " << ::min( c, d ) << std::endl;
	std::cout << "max( " << c << ", " << d << ") = " << ::max( c, d ) << std::endl;
	return 0;
}
