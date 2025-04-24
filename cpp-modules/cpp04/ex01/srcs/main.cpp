/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:53:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 01:05:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main()
{
	// No leaks:
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete (j);
	delete (i);

	// Test for deep copy:
	const Cat* dog = new Cat();
	dog->getBrain()->setIdea(0, "I want a bone");
	Cat *copy = new Cat(*dog);
	copy->getBrain()->setIdea(0, "I wanna play!");
	std::cout << "Original dog's idea: " << dog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copy dog's idea: " << copy->getBrain()->getIdea(0) << std::endl;
	delete(dog);
	delete(copy);
	// Main test:
	const Animal* animals[4];
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (i % 2)
			animals[i] = new Cat();
		else
			animals[i] = new Dog();
	}
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
		animals[i]->makeSound();
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
		delete (animals[i]);
	return (0);
}
