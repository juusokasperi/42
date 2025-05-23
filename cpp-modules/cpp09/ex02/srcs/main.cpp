/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:26:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/24 00:46:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static void					printNumBeforeSorting(std::vector<int> numbers);
static bool					isPositiveNumber(std::string s);
static std::vector<int32_t>	pushToVec(int argc, char **argv);
static std::deque<int32_t>	pushToDeq(std::vector<int> &numsVec);

int main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	try {
		std::vector<int32_t> numbersVec = pushToVec(argc - 1, argv + 1);
		std::deque<int32_t> numbersDeq = pushToDeq(numbersVec);
		printNumBeforeSorting(numbersVec);
		PmergeMe<std::deque<int32_t>>::fordJohnson(numbersDeq, false, true);
		PmergeMe<std::vector<int32_t>>::fordJohnson(numbersVec, true, false);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	return (0);
}

static void	printNumBeforeSorting(std::vector<int32_t> numbers)
{
	std::cout << std::setw(15) << std::left << "Before:" << "[";
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		std::cout << numbers[i];
		if (i + 1 != numbers.size())
			std::cout << " ";
	}
	std::cout << "]\n";
}

static bool isPositiveNumber(std::string s)
{
	size_t i = 0;
	if (s[0] == '-')
	{
		if (s.length() != 2 || s[1] != '0')
			return (false);
		return (true);
	}
	else if (s.length() > 1 && s[0] == '+')
		i++;
	while (i < s.length())
	{
		if (!std::isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static std::vector<int32_t>	pushToVec(int argc, char **argv)
{
	std::vector<int32_t>	nums;

	for (int i = 0; i < argc; ++i)
	{
		if (!isPositiveNumber(argv[i]))
			throw (std::runtime_error("Invalid input."));
		try {
			nums.push_back(std::stoi(argv[i]));
		} catch (std::exception &e) {
			throw (std::out_of_range("Integer must be within bounds of 0 to INT_MAX."));
		}
	}
	return (nums);
}

static std::deque<int32_t>	pushToDeq(std::vector<int> &numsVec)
{
	std::deque<int32_t>	nums;

	for (size_t i = 0; i < numsVec.size(); ++i)
		nums.push_back(numsVec[i]);
	return (nums);
}

