/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:53:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:30:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main() {
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const WrongAnimal* i = new WrongCat();
	const Animal* y = new Cat();

	std::cout	<< j->getType() << std::endl;
	std::cout << i->getType() << std::endl;
	std::cout << y->getType() << std::endl;
	i->makeSound();
	meta->makeSound();
	y->makeSound();
	delete(y);
	delete(meta);
	delete(j);
	delete(i);
	return 0;
}
