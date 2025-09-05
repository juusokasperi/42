/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:42:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 11:34:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "PmergeMe.hpp"

template<typename Container>
size_t PmergeMe<Container>::_comparisons = 0;

/**
 * Sorts the values using Ford-Johnson algorithm using index tracking.
**/
template<typename Container>
Container	PmergeMe<Container>::sort(const Container &values)
{
	if (values.size() <= 1)
		return values;
	_comparisons = 0;
	Container sortedIndices = sortIndices(values);
	Container result(values.size());
	for (size_t i = 0; i< values.size(); ++i)
		result[i] = values[sortedIndices[i]];
	return result;
}

/**
 * Sort a sequence when n <= 2
**/
template<typename Container>
Container	PmergeMe<Container>::sortSmall(const Container &values, size_t n)
{
	Container indices(n);
	if (n == 1)
		indices[0] = 0;
	else if (n == 2)
	{
		_comparisons++;
		if (values[0] <= values[1])
		{
			indices[0] = 0;
			indices[1] = 1;
		}
		else
		{
			indices[0] = 1;
			indices[1] = 0;
		}
	}
	return indices;
}

/**
 * Pairs adjacent elements, storing larger/smaller indices separately.
 * Updates pairMap to track which smaller index pairs with which larger.
**/
template<typename Container>
void PmergeMe<Container>::createPairs(const Container &values, Container &indices,
		Container &largerIndices, Container &smallerIndices, Container &pairMap, size_t n)
{
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		_comparisons++;
		if (values[indices[i]] <= values[indices[i + 1]])
		{
			largerIndices.push_back(indices[i + 1]);
			smallerIndices.push_back(indices[i]);
			pairMap[indices[i]] = indices[i + 1];
		}
		else
		{
			largerIndices.push_back(indices[i]);
			smallerIndices.push_back(indices[i + 1]);
			pairMap[indices[i + 1]] = indices[i];
		}
	}
}

/**
 * Reorders smaller indices to match the sorted order of their paired larger indices.
 * Maintains the pair relationships after recursive sorting of the larger indices.
**/
template<typename Container>
Container PmergeMe<Container>::orderToSortedLarger(Container smallerIndices,
		Container pairMap, Container sortedLargerIndices)
{
	Container reOrderedSmaller(smallerIndices.size());
	for (size_t i = 0; i < sortedLargerIndices.size(); ++i)
	{
		for (size_t j = 0; j < pairMap.size(); ++j)
		{
			if (pairMap[j] == -1)
				continue;
			else if (pairMap[j] == sortedLargerIndices[i])
			{
				reOrderedSmaller[i] = j;
				break ;
			}
		}
	}
	return reOrderedSmaller;
}

/**
 * The main Ford Johnson algorithm.
 * 1.	Pair elements, separate larger/smaller indices
 * 2.	Recursively sort larger elements
 * 3.	Build main chain from sorted larger indices
 * 4.	Insert smaller indices using Jacobsthal-ordered binary insertion
**/
template<typename Container>
Container PmergeMe<Container>::sortIndices(const Container &values)
{
	size_t n = values.size();
	if (n <= 2)
		return sortSmall(values, n);

	Container indices(n);
	for (size_t i = 0; i < n; ++i)
		indices[i] = i;
	Container largerIndices;
	Container smallerIndices;
	Container pairMap(n, -1);
	createPairs(values, indices, largerIndices, smallerIndices, pairMap, n);
	size_t oddIndex = -1;
	if (n % 2 == 1)
		oddIndex = indices[n - 1];

	Container largerValues(largerIndices.size());
	for (size_t i = 0; i < largerIndices.size(); ++i)
		largerValues[i] = values[largerIndices[i]];
	Container sortedLargerIndices = sortIndices(largerValues);
	for (size_t i = 0; i < sortedLargerIndices.size(); ++i)
		sortedLargerIndices[i] = largerIndices[sortedLargerIndices[i]];
	smallerIndices = orderToSortedLarger(smallerIndices, pairMap, sortedLargerIndices);

	Container mainChain;
	mainChain.insert(mainChain.end(), sortedLargerIndices.begin(), sortedLargerIndices.end());
	if (oddIndex != (size_t)-1)
		smallerIndices.push_back(oddIndex);
	if (!smallerIndices.empty())
	{
		Container insertionOrder = calculateInsertionOrder(smallerIndices.size());
		for (size_t j = 0; j < smallerIndices.size(); ++j)
		{
			size_t idx = insertionOrder[j];
			if (idx < smallerIndices.size())
			{
				size_t indexToInsert = smallerIndices[idx];
				binaryInsert(mainChain, values, indexToInsert, pairMap);
			}
		}
	}
	return mainChain;
}

/**
 * Binary insert with the optimization that the upper bound is the
 * pair of the inserted value.
**/
template<typename Container>
void PmergeMe<Container>::binaryInsert(Container &chain, const Container &values,
		size_t indexToInsert, const Container &pairMap)
{
	size_t pairIndex = pairMap[indexToInsert];
	size_t pairPos = 0;
	while (pairPos < chain.size() && static_cast<size_t>(chain[pairPos]) != pairIndex)
		pairPos++;
	size_t left = 0;
	size_t right = pairPos;
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		_comparisons++;
		if (values[indexToInsert] < values[chain[mid]])
			right = mid;
		else
			left = mid + 1;
	}
	chain.insert(chain.begin() + left, indexToInsert);
}

/**
 * Generates optimal insertion order using Jacobsthal sequence
 * The sequence (1, 1, 3, 5, 11, 21, ...) minimizes comparisons
 * by inserting elements in groups that maximize binary insertion efficiency.
 * Returns indices in the order the should be inserted into the main chain.
**/
template<typename Container>
Container PmergeMe<Container>::calculateInsertionOrder(size_t n)
{
	Container order;
	if (n <= 1)
	{
		if (n == 1)
			order.push_back(0);
		return order;
	}
	Container jacob = generateJacobsthal(n);
	Container used(n, 0);
	for (size_t i = 2; i < jacob.size() && static_cast<size_t>(jacob[i - 1]) < n; ++i)
	{
		for (size_t j = static_cast<size_t>(jacob[i - 1]);
		j > static_cast<size_t>(jacob[i - 2]) && j <= n; --j)
		{
			if (j - 1 < n && used[j - 1] == 0)
			{
				order.push_back(j - 1);
				used[j - 1] = 1;
			}
		}
	}
	for (int i = n - 1; i >= 0; --i)
	{
		if (used[i] == 0)
		{
			order.push_back(i);
			used[i] = 1;
		}
	}
	return order;
}

/**
 * Generates the Jacobsthal sequence: J(n) = J(n-1) + 2 * J(n-2)
**/
template<typename Container>
Container PmergeMe<Container>::generateJacobsthal(size_t n)
{
	Container jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	while (static_cast<size_t>(jacob.back()) < n)
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
	return jacob;
}

/**
 * Times the sorting, prints the sorted values if printSorted == true,
 * and checks against the theoretical maximum for n values if checkCompare == true
**/
template<typename Container>
void PmergeMe<Container>::fordJohnson(const Container &values, bool checkCompare, bool printSorted)
{
	auto start = std::chrono::high_resolution_clock::now();
	Container sorted = sort(values);
	auto end = std::chrono::high_resolution_clock::now();
	if (printSorted == true)
		printSortedNumbers(sorted);
	double duration =
		(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1000.0;
	std::string containerName = "container";
	if (typeid(Container) == typeid(std::vector<typename Container::value_type>))
		containerName = "std::vector";
	else if (typeid(Container) == typeid(std::deque<typename Container::value_type>))
		containerName = "std::deque";
	std::cout	<< "Time to process a range of " << std::setw(5) << std::right
				<< sorted.size() << " elements with " << containerName << ": "
				<< std::fixed << std::setprecision(6) << duration << " ms\n";
	if (checkCompare == true)
		checkComparisons(sorted.size(), _comparisons);
}

template<typename Container>
void PmergeMe<Container>::printSortedNumbers(const Container &sorted)
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

template<typename Container>
int PmergeMe<Container>::F(int n)
{
	int sum = 0;
	for (int k = 1; k <= n; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(std::log2(value)));
	}
	return (sum);
}

template<typename Container>
void PmergeMe<Container>::checkComparisons(size_t n, int comp)
{
	int max = F(n);
	if (comp <= max)
		std::cout << "\033[0;92mOK:\033[0m " << comp << " comparisons ";
	else
		std::cout << "\033[0;92mKO:\033[0m " << comp << " comparisons ";
	std::cout << "(max for n = " << n << " is " << max << ")\n";
}
