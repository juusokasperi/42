/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:21:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/03 18:36:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <random>
#include <ctime>

Base	*generate(void)
{
	std::mt19937	rng(std::time(nullptr));
	std::uniform_int_distribution<int>	dist(0, 2);
	int	random = dist(rng);
	switch (random)
	{
		case (0):
			return new A();
		case (1):
			return new B();
		case (2):
			return new C();
	}
	std::cerr << "Error generating object" << std::endl;
	return nullptr;
}

void	identify(Base *p)
{
	if (p == nullptr)
		std::cerr << "Pointer is nullptr, cannot identify type" << std::endl;
	else if (dynamic_cast<A*>(p))
		std::cout << "Pointer is of type A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Pointer is of type B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Pointer is of type C" << std::endl;
	else
		std::cerr << "Unknown type" << std::endl;
}

void	identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "Reference is of type A" << std::endl;
	}
	catch (std::bad_cast &e)
	{
		try
		{
			(void)dynamic_cast<B&>(p);
			std::cout << "Reference is of type B" << std::endl;
		}
		catch (std::bad_cast &e)
		{
			try
			{
				(void)dynamic_cast<C&>(p);
				std::cout << "Reference is of type C" << std::endl;
			}
			catch (std::bad_cast &e)
			{
				std::cerr << "Unknown type" << std::endl;
			}
		}
	}
}

int	main(void)
{
	std::cout	<< "\033[0;93m*** TEST 1 ***\033[0m"
				<< std::endl
				<< "Generate & identify\n"
				<< std::endl;
	Base	*obj = generate();
	identify(obj);
	identify(*obj);

	std::cout	<< "\n\033[0;93m*** TEST 2 ***\033[0m"
			<< std::endl
			<< "Try to identify a null pointer (works only for the pointer identify)\n"
			<< std::endl;
	identify(nullptr);

	std::cout	<< "\n\033[0;93m*** TEST 3 ***\033[0m"
				<< std::endl
				<< "Object is of class Base, in this case \"unknown type\".\n"
				<< std::endl;
	Base *obj2 = new Base();
	identify(obj2);
	identify(*obj2);

	delete obj;
	delete obj2;
	return 0;
}
