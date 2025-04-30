/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:26:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/30 16:27:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FordJohnsonVec.hpp"
#include "FordJohnsonDeq.hpp"

static void				numBeforeSorting(std::vector<int> numbers);
static bool				isPositiveNumber(std::string s);
static std::vector<int>	pushToVec(int argc, char **argv);
static std::deque<int>	pushToDeq(std::vector<int> &numsVec);

int main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	try {
		std::vector<int> numbersVec = pushToVec(argc - 1, argv + 1);
		std::deque<int> numbersDeq = pushToDeq(numbersVec);
		numBeforeSorting(numbersVec);
		FordJohnsonDeq::displaySorted(numbersDeq);
		FordJohnsonVec::displaySorted(numbersVec);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	return (0);
}

static void	numBeforeSorting(std::vector<int> numbers)
{
	std::cout << std::setw(15) << std::left << "Before:" << "[ ";
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

static std::vector<int>	pushToVec(int argc, char **argv)
{
	std::vector<int>	nums;

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

static std::deque<int>	pushToDeq(std::vector<int> &numsVec)
{
	std::deque<int>	nums;

	for (size_t i = 0; i < numsVec.size(); ++i)
		nums.push_back(numsVec[i]);
	return (nums);
}

