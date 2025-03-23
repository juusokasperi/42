/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:02:29 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/23 22:10:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int	main(void)
{
	Data		person = {35, "John"};
	uintptr_t	ptr;
	Data		*ret;

	ptr = Serializer::serialize(&person);
	ret = Serializer::deserialize(ptr);
	std::cout << "Person addr: " << &person << std::endl;
	std::cout << "Address as unsigned int: " << ptr << std::endl;
	std::cout << "Deserialized addr: " << ret << std::endl;
}
