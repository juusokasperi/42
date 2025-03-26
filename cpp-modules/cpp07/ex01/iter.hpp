/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:29:27 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 17:43:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

template<typename T, typename L, typename Func>
void	iter(T *arr, L len, Func func)
{
	for (int i = 0; i < (int)len; i++)
		func(arr[i]);
}

#endif /* ITER_HPP */
