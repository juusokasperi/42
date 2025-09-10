/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:31:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/10 10:13:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <algorithm>

template<typename Container>
class PmergeMe {
	private:
		static size_t	_comparisons;

		static Container	sortIndices(const Container &value);
		static Container	sortSmall(const Container &values, int32_t n);

		static void			createPairs(const Container &values, Container &largerIndices,
			Container &smallerIndices, Container &pairMap, int32_t n);
		static void			binaryInsert(Container &chain, const Container &values,
			int32_t indexToInsert, const Container &pairMap);

		static Container	generateJacobsthal(int32_t n);
		static Container	calculateInsertionOrder(int32_t n);
		static Container	orderToSortedLarger(Container smallerIndices,
			Container largerIndices, Container sortedLargerIndices);
	public:
		PmergeMe() = delete;
		PmergeMe(const PmergeMe &src) = delete;
		PmergeMe(PmergeMe &&other) = delete;
		PmergeMe& operator=(const PmergeMe &rhs) = delete;
		PmergeMe& operator=(PmergeMe &&other) = delete;
		~PmergeMe() = delete;

		static Container	sort(const Container &values, size_t &comparisons);
};

#include "PmergeMe.tpp"
