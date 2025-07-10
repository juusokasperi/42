/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/05 19:05:36 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Fixed.hpp"

static void subjectTest(void)
{
	std::cout << "\033[0;92m*** TEST IN SUBJECT ***\033[0m" << std::endl;
	try {
		Fixed a;
		Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

		std::cout << a << std::endl;
		std::cout << ++a << std::endl;
		std::cout << a << std::endl;
		std::cout << a++ << std::endl;
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << Fixed::max( a, b ) << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

static void testAllOperations(void)
{
	std::cout << "\n\033[0;92m*** TESTING CALCULATIONS AND INCREMENT/DECREMENT ***\033[0m" << std::endl;
	try {
		Fixed a(FIXED_FLOAT_MIN);
		Fixed const b( Fixed( 5.05f ) + Fixed( -100 ) );
		Fixed const c(Fixed(130.75f) / Fixed(4));
		Fixed const d(Fixed (500) * Fixed(1500.0f) );
		Fixed const e( Fixed( FIXED_FLOAT_MAX ) - Fixed( 2 ));

		std::cout << Fixed::min( a, b ) << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		std::cout << d << std::endl;
		std::cout << e << std::endl;
		a.setRawBits(0);
		if (a++ > 0)
			std::cout << "A is bigger than 0 and is now at " << a << std::endl;
		else
			std::cout << "A was incremented POST, so now it is " << a << std::endl;
		a.setRawBits(0);
		if (++a > 0)
			std::cout << "A is bigger than 0 and is now at " << a << std::endl;
		else
			std::cout << "A was incremented PRE, so now it is " << a << std::endl;
		if (a-- > 0)
			std::cout << "A is bigger than 0 and is now at " << a << std::endl;
		else
			std::cout << "A was decremented POST, so now it is " << a << std::endl;
		a.setRawBits(0);
		if (--a > 0)
			std::cout << "A is bigger than 0 and is now at " << a << std::endl;
		else
			std::cout << "A was decremented PRE, so now it is " << a << std::endl;
	} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
	}
}

static void	testOverflows(void)
{
	std::cout << "\n\033[0;92m*** TESTING CALCULATION OVERFLOWS ***\033[0m" << std::endl;
	try {
		Fixed a(Fixed((FIXED_INT_MAX / 2) + 1) * Fixed(2));
		std::cout << a << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		Fixed a(Fixed(5) / Fixed(0));
		std::cout << a << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		Fixed a(FIXED_INT_MAX - 2);
		std::cout << a.getRawBits() << std::endl;
		std::cout << a << std::endl;
		for (size_t i = 0; i < 512; ++i)
		{
			++a;
		}
		std::cout << a << std::endl;
		std::cout << a.getRawBits() << std::endl;
		++a;
		std::cout << a << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		Fixed a(FIXED_FLOAT_MIN + 1.0f);
		std::cout << a.getRawBits() << std::endl;
		std::cout << a << std::endl;
		for (size_t i = 0; i < 256; ++i)
			--a;
		std::cout << a << std::endl;
		std::cout << a.getRawBits() << std::endl;
		--a;
		std::cout << a << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int main(void)
{
	subjectTest();
	testAllOperations();
	testOverflows();
	return (0);
}
