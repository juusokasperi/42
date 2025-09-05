/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:54:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 09:48:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <list>
#include <vector>

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
	} catch (std::exception &e) {
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
	} catch (std::exception &e) {
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
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::vector<int>	vec = { 3, 2, 1, 0 };
		sp.addRange(vec.begin(), vec.end());
	} catch (std::exception &e) {
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
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		spEmpty.addNumber(1);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

static void copyTest(void)
{	
	std::cout << "\033[0;94m*** TEST COPY CONSTRUCTOR & ASSIGNMENT ***\033[0m" << std::endl;
	Span sp = Span(5);
	Span sp2 = sp;
	Span sp3(sp);
	std::vector<int>	vec = { 15, -40, 40, 10 };
	sp.addRange(vec.begin(), vec.end());
	std::cout << sp.shortestSpan() << std::endl;
	try {
		std::cout << sp2.shortestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << sp3.shortestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	Span sp4(sp);
	std::cout << sp4.shortestSpan() << std::endl;
	Span sp5 = sp;
    std::cout << sp5.shortestSpan() << std::endl;
}

static void moveTest(void)
{	
	std::cout << "\033[0;94m*** TEST MOVE CONSTRUCTOR & ASSIGNMENT ***\033[0m" << std::endl;
	Span sp = Span(5);
	std::vector<int>	vec = { 15, -40, 40, 10 };
	sp.addRange(vec.begin(), vec.end());
	std::cout << "  Printing shortestSpan on sp\n";	
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << "  Printing longestSpan on sp\n";	
	std::cout << sp.longestSpan() << std::endl;
	std::cout << "  Moving contents of sp to sp2 with move assignment, printing first shortestSpan of sp2, then trying to print sp\n";	
	Span sp2 = std::move(sp);
	std::cout << sp2.shortestSpan() << std::endl;
	try {
		std::cout << sp.shortestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << "  Moving contents of sp2 to sp3 with move constructor, printing first shortestSpan of sp3, then trying to print sp2\n";	
	Span sp3(std::move(sp2));
	std::cout << sp3.shortestSpan() << std::endl;
	try {
		std::cout << sp2.shortestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int	main(void)
{
	subjectTest();
	bigTest();
	addIteratorTest();
	invalidTest();
	copyTest();
	moveTest();
	return 0;
}
