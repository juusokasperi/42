/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FordJohnsonVec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:41:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/27 20:15:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

class FordJohnsonVec {
	private:
		static size_t	_comparisons;
		static std::vector<size_t> generateJacobsthal(size_t n);
		static std::vector<size_t> calculateInsertionOrder(size_t n);
		static std::vector<size_t> sortIndices(const std::vector<int> &values);
		static std::vector<size_t> sortSmall(const std::vector<int> &values, size_t n);
		static void createPairs(const std::vector<int> &values, std::vector<size_t> &indices,
			std::vector<size_t> &largerIndices, std::vector<size_t> &smallerIndices,
			std::vector<size_t> &pairMap, size_t n);
		static void binaryInsert(std::vector<size_t> &chain,
			const std::vector<int> &values, size_t indexToInsert,
			const std::vector<size_t> &pairMap);
		static size_t jacobsthalNumber(size_t n);
		static std::vector<size_t> orderToSortedLarger(std::vector<size_t> smallerIndices,
			std::vector<size_t> largerIndices, std::vector<size_t> sortedLargerIndices);
	public:
		static std::vector<int> sort(const std::vector<int> &values);
		static void displaySorted(const std::vector<int> &values);
};
