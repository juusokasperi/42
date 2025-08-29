/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:39:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/29 10:33:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <iomanip>

void	multiplyBy2(int &i) { i = i * 2; }
void	decrement(int &i) { i--; }
void	upperCase(char &c) { c = std::toupper(c); }
void	lowerCase(char &c) { c = std::tolower(c); }
void	addBar(std::string &s) { s += "_bar"; }
void	addFoo(std::string &s) { s = "foo_" + s; }

static void	test_numbers(void)
{
	int	numbers[] = { 0, 1, 2, 3 };
	std::cout << "Numbers before iteration:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << numbers[i] << " ";
	std::cout << std::endl << "Numbers after multiplying by 2:" << std::endl;
	iter(numbers, 4, multiplyBy2);
	for (int i = 0; i < 4; i++)
		std::cout << numbers[i] << " ";
	std::cout << std::endl << "Numbers after decrement:" << std::endl;
	iter(numbers, 4, decrement);
	for (int i = 0; i < 4; i++)
		std::cout << numbers[i] << " ";
	std::cout << std::endl << std::endl;
}

static void	test_char(void)
{
	char	chars[] = { 'y', 'x', 'b', 'c' };
	std::cout << "Chars before upperCasing:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << chars[i] << " ";
	std::cout << std::endl << "After:" << std::endl;
	iter(chars, 4, upperCase);
	for (int i = 0; i < 4; i++)
		std::cout << chars[i] << " ";
	std::cout << std::endl << "After lowercasing:" << std::endl;
	iter(chars, 4, lowerCase);
	for (int i = 0; i < 4; i++)
		std::cout << chars[i] << " ";
	std::cout << std::endl << std::endl;
}

static void	test_string(void)
{
	std::string	strings[] = { "hello", "world", "test", "string"};
	std::cout << "String before adding _bar:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << strings[i] << " ";
	std::cout << std::endl << "After:" << std::endl;
	iter(strings, 4, addBar);
	for (int i = 0; i < 4; i++)
		std::cout << strings[i] << " ";
	std::cout << std::endl << "After adding foo_:" << std::endl;
	iter(strings, 4, addFoo);
	for (int i = 0; i < 4; i++)
		std::cout << strings[i] << " ";
	std::cout << std::endl << std::endl;
}

int	main(void)
{
	test_numbers();
	test_char();
	test_string();

	return 0;
}
