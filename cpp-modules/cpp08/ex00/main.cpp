/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:42:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 09:33:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <list>
#include <vector>
#include <deque>

void runTest(void)
{
	std::cout << "\033[0;33m** Testing with Vector\033[0m\n";
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
		
	std::cout << "\033[0;33m** Testing with List\033[0m\n";
	std::list<int> lst = {10, 20, 30, 40, 50};
	std::list<int>::iterator lstIt = easyfind(lst, 50);
	if (lstIt != lst.end())
		std::cout << "Found 50 at index: " << std::distance(lst.begin(), lstIt) << std::endl;
	std::list<int>::iterator lstNotFound = easyfind(lst, 1);
	if (lstNotFound != lst.end())
		std::cout << "Found 1 at index " << std::distance(lst.begin(), lstNotFound) << std::endl;
	else
		std::cout << "Index not found\n";
		
	std::cout << "\033[0;33m** Testing with Deque\033[0m\n";
	std::deque<int> deq = {10, 20, 30, 40, 50};
	std::deque<int>::iterator deqIt = easyfind(deq, 10);
	if (deqIt != deq.end())
		std::cout << "Found 10 at index: " << std::distance(deq.begin(), deqIt) << std::endl;
	std::deque<int>::iterator deqNotFound = easyfind(deq, -500);
	if (deqNotFound != deq.end())
		std::cout << "Found -500 at index " << std::distance(deq.begin(), deqNotFound) << std::endl;
	else
		std::cout << "Index not found\n";
}

int	main(void)
{
	runTest();
	return (0);
}
