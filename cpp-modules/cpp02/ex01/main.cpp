/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/05 12:43:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Fixed.hpp"

static void	overflowTest(void);

int	main(void)
{
	try {
		Fixed		a;
		Fixed const	b( 10 );
		Fixed const	c( 42.42f );
		Fixed const	d( b );

		a = Fixed( 1234.4321f );
		std::cout << "a is " << a << std::endl;
		std::cout << "b is " << b << std::endl;
		std::cout << "c is " << c << std::endl;
		std::cout << "d is " << d << std::endl;
		std::cout << "a is " << a.toInt() << " as integer" << std::endl;
		std::cout << "b is " << b.toInt() << " as integer" << std::endl;
		std::cout << "c is " << c.toInt() << " as integer" << std::endl;
		std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	} catch (std::overflow_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	overflowTest();
	return (0);
}

static void	overflowTest(void)
{
	std::cout << std::endl << "\033[0;33m*** TESTING OVERFLOWS ***\033[0m" << std::endl;
	try {
		Fixed a = Fixed(FIXED_FLOAT_MAX + 1);
	} catch (std::overflow_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		Fixed a = Fixed(FIXED_FLOAT_MIN - 1);
	} catch (std::overflow_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		Fixed a = Fixed(FIXED_INT_MAX + 1);
	} catch (std::overflow_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		Fixed a = Fixed(FIXED_INT_MIN - 1);
	} catch (std::overflow_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
