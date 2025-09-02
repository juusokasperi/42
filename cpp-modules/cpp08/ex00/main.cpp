/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:42:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/01 19:07:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <list>
#include <vector>

void runTest(void)
{
	std::vector<int> vec = {1, 2, 3, 4, 5};
	std::vector<int>::iterator vecIt = easyfind(vec, 3);
	if (vecIt != vec.end())
		std::cout << "Found 3 at index: " << std::distance(vec.begin(), vecIt) << std::endl;
	else
		std::cout << "Index not found\n";

	std::vector<int>::iterator vecNotFound = easyfind(vec, 10);
	if (vecNotFound != vec.end())
		std::cout << "Found 10 at index " << std::distance(vec.begin(), vecNotFound) << std::endl;
	else
		std::cout << "Index not found\n";
		

	std::list<int> lst = {10, 20, 30, 40, 50};
	std::list<int>::iterator lstIt = easyfind(lst, 30);
	if (lstIt != lst.end())
		std::cout << "Found 30 at index: " << std::distance(lst.begin(), lstIt) << std::endl;
	std::list<int>::iterator lstNotFound = easyfind(lst, 1);
	if (lstNotFound != lst.end())
		std::cout << "Found 10 at index " << std::distance(lst.begin(), lstNotFound) << std::endl;
	else
		std::cout << "Index not found\n";
}

int	main(void)
{
	runTest();
	return (0);
}
