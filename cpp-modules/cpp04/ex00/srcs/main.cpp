/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:53:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/24 12:59:30 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main()
{
	{
		std::cout	<< "\033[0;92m*** TESTING ANIMALS ***\033[0m" << std::endl;

		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout	<< j->getType() << std::endl;
		j->makeSound();
		std::cout << i->getType() << std::endl;
		i->makeSound();
		std::cout	<< meta->getType() << std::endl;
		meta->makeSound();
		delete(meta);
		delete(j);
		delete(i);
	}
	{
		std::cout	<< "\n\033[0;92m*** TESTING WRONG ANIMALS ***\033[0m" << std::endl;
		const WrongAnimal* meta = new WrongAnimal();
		const WrongAnimal* i = new WrongCat();

		std::cout << i->getType() << std::endl;
		i->makeSound();
		std::cout << meta->getType() << std::endl;
		meta->makeSound();
		delete(meta);
		delete(i);
	}
	return (0);
}
