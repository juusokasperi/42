/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:21:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/27 10:49:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>

template<typename T>
typename T::iterator	easyfind(T &container, int toFind)
{
	auto i = std::find(container.begin(), container.end(), toFind);

	if (i == container.end())
		throw std::runtime_error("Element not found in container.");
	return (i);
}

#endif /* EASYFIND_HPP */
