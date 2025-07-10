/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:54:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/27 15:16:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <list>

static void	subjectTest(void)
{
	std::cout << "\033[0;94m*** TEST SUPPLIED BY SUBJECT***\033[0m" << std::endl;
	Span sp = Span(5);
	try {
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

static void bigTest(void)
{
	std::cout << "\033[0;94m*** TEST WITH 50 000 NUMBERS***\033[0m" << std::endl;
	Span sp = Span(50000);
	try {
		sp.addNumber(150000);
		sp.addRange(49999);
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

static void	addIteratorTest(void)
{
	std::cout << "\033[0;94m*** TEST WITH ITERATORS ***\033[0m" << std::endl;
	std::vector<int>	vec = { 15, -40, 40, 10 };
	std::list<int>		lst = { -500, 0, 4, 8, 120, 128};
	Span sp = Span(10);
	try {
		sp.addRange(vec.begin(), vec.end());
		sp.addRange(lst.begin(), lst.end());
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

static void	invalidTest(void)
{
	std::cout << "\033[0;94m*** TEST EXCEEDING MAX SIZE ***\033[0m" << std::endl;
	Span sp = Span(5);
	Span spEmpty = Span(0);
	try {
		sp.addRange(6);
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		spEmpty.addNumber(1);
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int	main(void)
{
	subjectTest();
	bigTest();
	addIteratorTest();
	invalidTest();
	return 0;
}
