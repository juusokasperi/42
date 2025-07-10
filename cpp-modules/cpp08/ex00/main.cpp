/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:42:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/27 11:17:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <list>

void runTest(void)
{
	std::vector<int> vec = {1, 2, 3, 4, 5};
	try {
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Found 3 at index: " << std::distance(vec.begin(), it) << std::endl;

		std::vector<int>::iterator notFound = easyfind(vec, 10);
		std::cout << "Found 10 at index " << std::distance(vec.begin(), notFound) << std::endl;
	} catch (const std::runtime_error& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::list<int> lst = {10, 20, 30, 40, 50};
	try {
		std::list<int>::iterator it = easyfind(lst, 30);
		std::cout << "Found 30 at index: " << std::distance(lst.begin(), it) << std::endl;
		std::list<int>::iterator notFound = easyfind(lst, 1);
		std::cout << "Found 10 at index " << std::distance(lst.begin(), notFound) << std::endl;
	} catch (const std::runtime_error& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int	main(void)
{
	runTest();
	return (0);
}
