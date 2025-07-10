/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:02:29 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/03 18:29:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int	main(void)
{
	Data		*person = new Data{ 35, "John" };
	uintptr_t	ptr;
	Data		*ret;

	ptr = Serializer::serialize(person);
	ret = Serializer::deserialize(ptr);
	std::cout << "Person addr: " << person << "\n";
	std::cout << "Address as unsigned int ptr: " << ptr << "\n";
	std::cout << "Deserialized addr: " << ret << "\n\n";

	std::cout << "Person name " << person->name << " and age " << person->age << "\n";
	std::cout << "Return name " << ret->name << " and age " << ret->age << "\n";
	delete person;
}
