/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FordJohnsonDeq.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:41:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/30 16:29:06 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <iostream>
#include <iomanip>
#include <chrono>

class FordJohnsonDeq {
	private:
		static size_t	_comparisons;
		static std::deque<size_t> generateJacobsthal(size_t n);
		static std::deque<size_t> calculateInsertionOrder(size_t n);
		static std::deque<size_t> sortIndices(const std::deque<int> &values);
		static std::deque<size_t> sortSmall(const std::deque<int> &values, size_t n);
		static void createPairs(const std::deque<int> &values, std::deque<size_t> &indices,
			std::deque<size_t> &largerIndices, std::deque<size_t> &smallerIndices,
			std::deque<size_t> &pairMap, size_t n);
		static void binaryInsert(std::deque<size_t> &chain,
			const std::deque<int> &values, size_t indexToInsert,
			const std::deque<size_t> &pairMap);
		static size_t jacobsthalNumber(size_t n);
		static std::deque<size_t> orderToSortedLarger(std::deque<size_t> smallerIndices,
			std::deque<size_t> largerIndices, std::deque<size_t> sortedLargerIndices);
	public:
		static std::deque<int> sort(const std::deque<int> &values);
		static void displaySorted(const std::deque<int> &values);
};
