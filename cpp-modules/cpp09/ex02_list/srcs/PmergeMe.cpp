#include "PmergeMe.hpp"

/**
 * Sorts the container using index-based tracking
**/
template<>
std::list<int32_t> PmergeMe<std::list<int32_t>>::sort(const std::list<int32_t> &values, size_t &comparisons)
{
	comparisons = 0;
	if (values.size() <= 1)
		return values;
	std::list<int32_t> sortedIndices = sortIndices(values);
	std::list<int32_t> sorted;
	for (int32_t idx : sortedIndices) {
		auto it = values.begin();
		std::advance(it, idx);
		sorted.push_back(*it);
	}
	comparisons = _comparisons;
	return sorted;
}

/**
 * Sort a sequence when n <= 2
**/
template<>
std::list<int32_t>	PmergeMe<std::list<int32_t>>::sortSmall(const std::list<int32_t> &values, int32_t n)
{
	std::list<int32_t> indices;
	if (n == 1)
		indices.push_back(0);
	else if (n == 2)
	{
		_comparisons++;
		auto itFirst = values.begin();
		auto itSecond = std::next(itFirst);
		if (*itFirst <= *itSecond)
		{
			indices.push_back(0);
			indices.push_back(1);
		}
		else
		{
			indices.push_back(1);
			indices.push_back(0);
		}
	}
	return indices;
}

/**
 * Pairs adjacent elements, storing larger/smaller indices separately.
 * Updates pairMap to track which smaller index pairs with which larger.
**/
template<>
void PmergeMe<std::list<int32_t>>::createPairs(const std::list<int32_t> &values,
	std::list<int32_t> &largerIndices, std::list<int32_t> &smallerIndices,
	std::list<int32_t> &pairMap, int32_t n)
{
	(void)n;
	int32_t i = 0;
	auto itPairSet = pairMap.begin();
	for (auto it = values.begin(); it != values.end(); std::advance(it, 2))
	{
		auto nextIt = std::next(it);
		if (nextIt == values.end())
			break;

		_comparisons++;
		if (*it <= *nextIt)
		{
			largerIndices.push_back(i + 1);
			smallerIndices.push_back(i);
			std::advance(itPairSet, i);
			pairMap.push_back(i + 1);
			pairMap.push_back(-1);
		}
		else
		{
			largerIndices.push_back(i);
			smallerIndices.push_back(i + 1);
			pairMap.push_back(-1);
			pairMap.push_back(i);
		}
		i += 2;
	}
}

/**
 * Reorders smaller indices to match the sorted order of their paired larger indices.
 * Maintains the pair relationships after recursive sorting of the larger indices.
**/
template<>
std::list<int32_t> PmergeMe<std::list<int32_t>>::orderToSortedLarger(std::list<int32_t> smallerIndices,
		std::list<int32_t> pairMap, std::list<int32_t> sortedLargerIndices)
{
	(void)smallerIndices;
	std::list<int32_t> reOrderedSmaller;
	for (auto sortedIt = sortedLargerIndices.begin(); sortedIt != sortedLargerIndices.end(); ++sortedIt)
	{
		int32_t j = 0;
		for (auto pairIt = pairMap.begin(); pairIt != pairMap.end(); ++pairIt, ++j)
		{
			if (*pairIt == -1)
				continue;
			else if (*pairIt == *sortedIt)
			{
				reOrderedSmaller.push_back(j);
				break;
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
template<>
std::list<int32_t> PmergeMe<std::list<int32_t>>::sortIndices(const std::list<int32_t> &values)
{
	int32_t n = static_cast<int32_t>(values.size());
	if (n <= 2)
		return sortSmall(values, n);

	std::list<int32_t> largerIndices;
	std::list<int32_t> smallerIndices;
	std::list<int32_t> pairMap;
	createPairs(values, largerIndices, smallerIndices, pairMap, n);
	int32_t oddIndex = -1;
	if (n % 2 == 1)
		oddIndex = n - 1;
	std::list<int32_t> largerValues;
	for (int32_t idx : largerIndices) {
		auto it = values.begin();
		std::advance(it, idx);
		largerValues.push_back(*it);
	}

	std::list<int32_t> sortedLargerSubIndices = sortIndices(largerValues);
	std::list<int32_t> sortedLargerIndices;
	for (int32_t subIdx : sortedLargerSubIndices) {
		auto it = largerIndices.begin();
		std::advance(it, subIdx);
		sortedLargerIndices.push_back(*it);
	}
	smallerIndices = orderToSortedLarger(smallerIndices, pairMap, sortedLargerIndices);

	std::list<int32_t> mainChain;
	mainChain.insert(mainChain.end(), sortedLargerIndices.begin(), sortedLargerIndices.end());
	if (oddIndex != -1)
		smallerIndices.push_back(oddIndex);

	if (!smallerIndices.empty())
	{
		std::list<int32_t> insertionOrder = calculateInsertionOrder(static_cast<int32_t>(smallerIndices.size()));
		for (size_t idx : insertionOrder)
		{
			if (idx < smallerIndices.size())
			{
				auto idxToInsertIt = smallerIndices.begin();
				std::advance(idxToInsertIt, idx);
				int32_t indexToInsert = *idxToInsertIt;
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
template<>
void PmergeMe<std::list<int32_t>>::binaryInsert(std::list<int32_t> &chain, const std::list<int32_t> &values,
		int32_t indexToInsert, const std::list<int32_t> &pairMap)
{
	auto indexIt = pairMap.begin();
	std::advance(indexIt, indexToInsert);
	auto it = std::find(chain.begin(), chain.end(), *indexIt);
	auto valueIt = values.begin();
	std::advance(valueIt, indexToInsert);

	size_t right = std::distance(chain.begin(), it);
	size_t left = 0;

	while (left < right)
	{
		auto chainIt = chain.begin();
		size_t mid = left + (right - left) / 2;
		std::advance(chainIt, mid);
		auto midValueIt = values.begin();
		std::advance(midValueIt, *chainIt);
		_comparisons++;
		if (*valueIt < *midValueIt)
			right = mid;
		else
			left = mid + 1;
	}
	auto insertionIt = chain.begin();
	std::advance(insertionIt, left);
	chain.insert(insertionIt, indexToInsert);
}

/**
 * Generates optimal insertion order using Jacobsthal sequence
 * The sequence (1, 1, 3, 5, 11, 21, ...) minimizes comparisons
 * by inserting elements in groups that maximize binary insertion efficiency.
 * Returns indices in the order the should be inserted into the main chain.
**/
template<>
std::list<int32_t> PmergeMe<std::list<int32_t>>::calculateInsertionOrder(int32_t n)
{
	std::list<int32_t> order;
	if (n <= 1)
	{
		if (n == 1)
			order.push_back(0);
		return order;
	}
	std::list<int32_t> jacob = generateJacobsthal(n);
	auto previousJacobIt = jacob.begin();
	auto currentJacobIt = std::next(previousJacobIt);
	while (currentJacobIt != jacob.end())
	{
		int32_t currentJacob = *currentJacobIt;
		while (currentJacob > *previousJacobIt)
		{
			order.push_back(currentJacob - 1);
			--currentJacob;
		}
		++previousJacobIt;
		++currentJacobIt;
	}
	for (int32_t i = n; i > jacob.back(); --i)
		order.push_back(i - 1);
	return order;
}

/**
 * Generates the Jacobsthal sequence: J(n) = J(n-1) + 2 * J(n-2)
**/
template<>
std::list<int32_t> PmergeMe<std::list<int32_t>>::generateJacobsthal(int32_t n)
{
	std::list<int32_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n)
	{
		auto lastIt = jacob.end();
		--lastIt;
		auto secondLastIt = lastIt;
		--secondLastIt;
		int32_t jacobNumber = *lastIt + 2 * (*secondLastIt);
		if (jacobNumber > n)
			break;
		jacob.push_back(jacobNumber);
	}
	return jacob;
}
