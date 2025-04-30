/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FordJohnsonVec.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:38:01 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/27 20:34:23by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FordJohnsonVec.hpp"

size_t FordJohnsonVec::_comparisons = 0;

// static void	debugVec(std::vector<size_t> &indices, const std::vector<int> &values)
// {
// 	std::cout << "Original:\n";
// 	for (size_t i = 0; i < values.size(); ++i)
// 	{
// 		std::cout << "[" << i << "] " << values[i] << "\n";
// 	}
// 	std::cout << "Sorted:\n";
// 	for (size_t i = 0; i < indices.size(); ++i)
// 	{
// 		std::cout << "[" << indices[i] << "]" << values[indices[i]] << "\n";
// 	}
// }

std::vector<int> FordJohnsonVec::sort(const std::vector<int> &values)
{
	if (values.size() <= 1)
		return values;
	_comparisons = 0;
	std::vector<size_t> sortedIndices = sortIndices(values);
	//debugVec(sortedIndices, values);
	std::vector<int> result(values.size());
	for (size_t i = 0; i < values.size(); ++i)
		result[i] = values[sortedIndices[i]];
	return result;
}

/*
	For small (n <=2) values, sort manually with just 1 comparison.
*/
std::vector<size_t> FordJohnsonVec::sortSmall(const std::vector<int> &values, size_t n)
{
	std::vector<size_t> indices(n);

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
	return (indices);
}

/*
	We store the indexes of the values in two containers (largerIndices, smallerIndices)
	Additional pairMap container tracks which indexes are paired with each other.
*/
void	FordJohnsonVec::createPairs(const std::vector<int> &values, std::vector<size_t> &indices,
		std::vector<size_t> &largerIndices, std::vector<size_t> &smallerIndices,
		std::vector<size_t> &pairMap, size_t n)
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

/*
	After we have sorted the larger indexes, we move the indexes of the
	smallerIndices container to match the positions.
*/
std::vector<size_t> FordJohnsonVec::orderToSortedLarger(std::vector<size_t> smallerIndices,
	std::vector<size_t> pairMap, std::vector<size_t> sortedLargerIndices)
{
	std::vector<size_t> reorderedSmaller(smallerIndices.size());

	for (size_t i = 0; i < sortedLargerIndices.size(); ++i)
	{
		for (size_t j = 0; j < pairMap.size(); ++j)
		{
			if (pairMap[j] == (size_t) -1)
				continue ;
			else if (pairMap[j] == sortedLargerIndices[i])
			{
				reorderedSmaller[i] = j;
				break ;
			}
		}
	}
	return (reorderedSmaller);
}
/*
	Main part of the algorithm - keeps track of the pairs using indexes.

	First, we pair the numbers to containers. One stores the indexes to the
	smaller elements of the pairs, another stores the indexes to the larger ones
	and one container keeps track of the relation of the indexes.

*/
std::vector<size_t> FordJohnsonVec::sortIndices(const std::vector<int> &values)
{
	size_t n = values.size();

	if (n <= 2)
		return (sortSmall(values, n));
	std::vector<size_t> indices(n);
	for (size_t i = 0; i < n; ++i)
		indices[i] = i;
	std::vector<size_t> largerIndices;
	std::vector<size_t> smallerIndices;
	std::vector<size_t> pairMap(n, -1);
	createPairs(values, indices, largerIndices, smallerIndices, pairMap, n);
	size_t oddIndex = -1;
	if (n % 2 == 1)
		oddIndex = indices[n - 1];
	std::vector<size_t> sortedLargerIndices = sortIndices(
		[&values, &largerIndices]() {
			std::vector<int> largerValues(largerIndices.size());
			for (size_t i = 0; i < largerIndices.size(); ++i)
				largerValues[i] = values[largerIndices[i]];
			return (largerValues);
		}()
	);
	for (size_t i = 0; i < sortedLargerIndices.size(); ++i)
		sortedLargerIndices[i] = largerIndices[sortedLargerIndices[i]];
	smallerIndices = orderToSortedLarger(smallerIndices, pairMap, sortedLargerIndices);

	std::vector<size_t> mainChain;
	mainChain.insert(mainChain.end(), sortedLargerIndices.begin(), sortedLargerIndices.end());
	if (oddIndex != (size_t)-1)
		smallerIndices.push_back(oddIndex);
	if (!smallerIndices.empty())
	{
		std::vector<size_t> insertionOrder = calculateInsertionOrder(smallerIndices.size());
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
	return (mainChain);
}

/*
	Binary insertion of the values. The Ford-Johnson optimization here is
	if we are f.ex. inserting value b3, we know the search area is between 0 - pos(a3)
	rather than 0 - chain.size().
*/
void FordJohnsonVec::binaryInsert(std::vector<size_t> &chain,
	const std::vector<int> &values, size_t indexToInsert,
	const std::vector<size_t> &pairMap)
{
	size_t pairIndex = pairMap[indexToInsert];
	size_t pairPos = 0;
	while (pairPos < chain.size() && chain[pairPos] != pairIndex)
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

/*
	Calculate the order of insertion for the smallerIndices into the mainChain
	using the Jacobsthal sequence.
*/
std::vector<size_t> FordJohnsonVec::calculateInsertionOrder(size_t n)
{
	std::vector<size_t> order;
	if (n <= 1)
	{
		if (n == 1)
			order.push_back(0);
		return order;
	}
	std::vector<size_t> jacob = generateJacobsthal(n);
	std::vector<bool> used(n, false);
	for (size_t i = 2; i < jacob.size() && jacob[i - 1] < n; ++i) {
		for (size_t j = jacob[i - 1]; j > jacob[i - 2] && j <= n; --j)
		{
			if (j - 1 < n && !used[j - 1])
			{
				order.push_back(j - 1);
				used[j - 1] = true;
			}
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		if (!used[i]) {
			order.push_back(i);
			used[i] = true;
		}
	}
	return order;
}

std::vector<size_t> FordJohnsonVec::generateJacobsthal(size_t n)
{
	std::vector<size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n) {
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
	}
	return (jacob);
}

static int F(int n)
{
	int sum = 0;
	for (int k = 1; k <= n; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}
	return (sum);
}

static void checkComparisons(size_t n, int comp)
{
	int	max = F(n);
	if (comp <= max)
		std::cout	<< "\033[0;92mOK:\033[0m " << comp << " comparisons ";
	else
		std::cout	<< "\033[0;91mKO:\033[0m " << comp << " comparisons ";
	std::cout << "(max for n = " << n << " is " << max << ")\n";
}

void FordJohnsonVec::displaySorted(const std::vector<int> &values)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<int> sorted = sort(values);
	auto end = std::chrono::high_resolution_clock::now();
	double duration =
		(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) / 1000.0;
	std::cout << "Time to process a range of " << std::setw(5) << std::right
	<< sorted.size() << " elements with std::vector: "
	<< std::fixed << std::setprecision(6) << duration << " ms\n";
	checkComparisons(sorted.size(), _comparisons);
}
