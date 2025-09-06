/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:26:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/06 22:32:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

template<typename Container>
static void					printSortedNumbers(const Container &sorted);
template<typename Container>
static void					printNumBeforeSorting(Container &numbers);
static std::vector<int32_t>	pushToVec(int argc, char **argv);
static void					checkComparisons(size_t n, size_t comp);

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 100000)
	{
		std::cerr << "Must supply 1-100000 numbers for sorting.\n";
		return (1);
	}
	try {
		std::vector<int32_t> numbersVec = pushToVec(argc - 1, argv + 1);
		std::deque<int32_t> numbersDeq(numbersVec.begin(), numbersVec.end());
		printNumBeforeSorting(numbersVec);
		size_t comparisons = 0;

		// Time sorting of deque
		auto start = std::chrono::high_resolution_clock::now();
		numbersDeq = PmergeMe<std::deque<int32_t>>::sort(numbersDeq, comparisons);
		auto end = std::chrono::high_resolution_clock::now();
		double durationDeq = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1000.0;

		// Time sorting of vector
		start = std::chrono::high_resolution_clock::now();
		numbersVec = PmergeMe<std::vector<int32_t>>::sort(numbersVec, comparisons);
		end = std::chrono::high_resolution_clock::now();
		double durationVec = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1000.0;

		printSortedNumbers(numbersVec);
		std::cout	<< "Time to process a range of " << std::setw(5) << std::right
				<< numbersDeq.size() << " elements with std::deque:  "
				<< std::fixed << std::setprecision(6) << durationDeq << " ms\n";
		std::cout	<< "Time to process a range of " << std::setw(5) << std::right
				<< numbersVec.size() << " elements with std::vector: "
				<< std::fixed << std::setprecision(6) << durationVec << " ms\n";
		// Check that the amount of comparisons is within the limits of FJ algorithm
		checkComparisons(numbersVec.size(), comparisons);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	return (0);
}

template<typename Container>
static void	printNumBeforeSorting(Container &numbers)
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
		for (size_t j = 1; j < s.length(); ++j)
		{
			if (s[j] != '0')
				return false;
		}
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

template<typename Container>
static void printSortedNumbers(const Container &sorted)
{
	std::cout << std::setw(15) << std::left << "After:" << "[";
	for (size_t i = 0; i < sorted.size(); ++i)
	{
		std::cout << sorted[i];
		if (i + 1 != sorted.size())
			std::cout << " ";
	}
	std::cout << "]\n";
}

static void checkComparisons(size_t n, size_t comp)
{
	size_t max = 0;
	for (size_t k = 1; k <= n; ++k)
	{
		double value = (3.0 / 4.0) * k;
		max += static_cast<size_t>(ceil(std::log2(value)));
	}

	if (comp <= max)
		std::cout << "\033[0;92mOK:\033[0m " << comp << " comparisons ";
	else
		std::cout << "\033[0;92mKO:\033[0m " << comp << " comparisons ";
	std::cout << "(max for n = " << n << " is " << max << ")\n";
}
