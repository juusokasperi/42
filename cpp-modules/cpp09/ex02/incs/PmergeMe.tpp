/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:42:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/09 14:45:43by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "PmergeMe.hpp"

template<typename Container>
size_t PmergeMe<Container>::_comparisons = 0;

/**
 * Sort a sequence when n <= 2
**/
template<typename Container>
Container	PmergeMe<Container>::sortSmall(const Container &values, int32_t n)
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
void PmergeMe<Container>::createPairs(const Container &values, Container &largerIndices,
	Container &smallerIndices, Container &pairMap, int32_t n)
{
	for (int32_t i = 0; i + 1 < n; i += 2)
	{
		_comparisons++;
		if (values[i] <= values[i + 1])
		{
			largerIndices.push_back(i + 1);
			smallerIndices.push_back(i);
			pairMap[i] = i + 1;
		}
		else
		{
			largerIndices.push_back(i);
			smallerIndices.push_back(i + 1);
			pairMap[i + 1] = i;
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
				reOrderedSmaller[i] = static_cast<int32_t>(j);
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
	int32_t n = static_cast<int32_t>(values.size());
	if (n <= 2)
		return sortSmall(values, n);

	Container largerIndices;
	Container smallerIndices;
	Container pairMap(n, -1);
	createPairs(values, largerIndices, smallerIndices, pairMap, n);
	int32_t oddIndex = -1;
	if (n % 2 == 1)
		oddIndex = n - 1;

	Container largerValues(largerIndices.size());
	std::transform(largerIndices.begin(), largerIndices.end(), largerValues.begin(),
		[&](int32_t idx) { return values[idx]; });
	Container sortedLargerIndices = sortIndices(largerValues);
	std::transform(sortedLargerIndices.begin(), sortedLargerIndices.end(),
		sortedLargerIndices.begin(), [&](int32_t idx) { return largerIndices[idx]; });
	smallerIndices = orderToSortedLarger(smallerIndices, pairMap, sortedLargerIndices);

	Container mainChain;
	mainChain.insert(mainChain.end(), sortedLargerIndices.begin(), sortedLargerIndices.end());
	if (oddIndex != -1)
		smallerIndices.push_back(oddIndex);
	if (!smallerIndices.empty())
	{
		Container insertionOrder = calculateInsertionOrder(static_cast<int32_t>(smallerIndices.size()));
		for (size_t j = 0; j < smallerIndices.size(); ++j)
		{
			size_t idx = insertionOrder[j];
			if (idx < smallerIndices.size())
			{
				int32_t indexToInsert = smallerIndices[idx];
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
		int32_t indexToInsert, const Container &pairMap)
{
	auto it = std::find(chain.begin(), chain.end(), pairMap[indexToInsert]);
	size_t pairPos = std::distance(chain.begin(), it);
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
Container PmergeMe<Container>::calculateInsertionOrder(int32_t n)
{
	Container order;
	if (n <= 1)
	{
		if (n == 1)
			order.push_back(0);
		return order;
	}
	Container jacob = generateJacobsthal(n);
	for (size_t i = 1; i < jacob.size(); ++i)
	{
		int32_t currentJacob = jacob[i];
		int32_t previousJacob = jacob[i - 1];
		while (currentJacob > previousJacob)
		{
			order.push_back(currentJacob - 1);
			--currentJacob;
		}
	}
	for (int32_t i = n; i > jacob.back(); --i)
		order.push_back(i - 1);
	return order;
}

/**
 * Generates the Jacobsthal sequence: J(n) = J(n-1) + 2 * J(n-2)
**/
template<typename Container>
Container PmergeMe<Container>::generateJacobsthal(int32_t n)
{
	Container jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n)
	{
		int32_t jacobNumber = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		if (jacobNumber > n)
			break;
		jacob.push_back(jacobNumber);
	}
	return jacob;
}

/**
 * Sorts the container using index-based tracking
**/
template<typename Container>
Container PmergeMe<Container>::sort(const Container &values, size_t &comparisons)
{
	comparisons = 0;
	if (values.size() <= 1)
		return values;
	Container sortedIndices = sortIndices(values);
	Container sorted(values.size());
	for (size_t i = 0; i < values.size(); ++i)
		sorted[i] = values[sortedIndices[i]];
	comparisons = _comparisons;
	return sorted;
}
