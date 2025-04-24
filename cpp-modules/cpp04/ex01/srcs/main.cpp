/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:53:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/24 16:14:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

// Simple leak test, we allocate a dog and a cat and delete them
static void	leakTest()
{
	std::cout	<< "\033[0;32m*** SIMPLE LEAK TEST ***\033[0m" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete (j);
	delete (i);
}

// Test for deep copy - create a Cat with an idea, copy that cat and override
// the idea from the copy and see if it affects the original Cat.
static void	deepCopyTest()
{
	std::cout	<< "\033[0;32m*** TEST DEEP COPY ***\033[0m" << std::endl;
	const Cat* catOne = new Cat();
	catOne->getBrain()->setIdea(0, "I should sleep.");
	const Cat* catTwo = new Cat(*catOne);
	catTwo->getBrain()->setIdea(0, "I wanna play!");

	std::cout << "Original cat's idea: " << catOne->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copy cat's idea: " << catTwo->getBrain()->getIdea(0) << std::endl;
	delete(catOne);
	delete(catTwo);
}

static void	subjectTest()
{
	std::cout	<< "\033[0;32m*** SUBJECT TEST ***\033[0m" << std::endl;
	const Animal* animals[12];
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
}

int main(int argc, char **argv)
{
	std::string	usage = "Usage: " + std::string(argv[0]) + " <subject>/<leak>/<deep>";
	if (argc != 2)
		std::cout << usage << std::endl;
	else
	{
		std::string	arg = argv[1];
		if (arg == "subject")
			subjectTest();
		else if (arg == "leak")
			leakTest();
		else if (arg == "deep")
			deepCopyTest();
		else
		{
			std::cerr << "Invalid command.\n" << usage << std::endl;
			return (1);
		}
	}
	return (0);
}
