/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:35:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/24 17:18:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"

static void	fullInventory()
{
	std::cout << "\033[0;32m *** TESTING FULL INVENTORY ***\033[0m" << std::endl;
	IMateriaSource* src = new MateriaSource();
	std::cout << std::endl;

	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(src->createMateria("ice"));
	std::cout << std::endl;

	ICharacter* joe = new Character("Joe");
	std::cout << std::endl;

	AMateria* ice;
	AMateria* ice2;
	AMateria* cure;
	AMateria* cure2;
	ice = src->createMateria("ice");
	cure = src->createMateria("cure");
	std::cout << std::endl;

	ice2 = ice->clone();
	cure2 = ice->clone();
	std::cout << std::endl;

	joe->unequip(0);
	joe->unequip(1);
	joe->unequip(2);
	joe->unequip(3);
	joe->unequip(4);
	std::cout << std::endl;

	joe->equip(ice);
	joe->equip(cure);
	joe->equip(ice2);
	joe->equip(cure2);
	joe->equip(ice);
	joe->equip(cure);

	delete (joe);
	delete (src);
}

static void	subject()
{
	std::cout << "\033[0;32m *** TESTING SUBJECT TEST ***\033[0m" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	me->unequip(0);
	delete (bob);
	delete (me);
	delete (src);
}

int	main(int argc, char **argv)
{
	std::string usage = "Usage: " + (std::string)argv[0] + " <fullInv>/<subject>";
	if (argc != 2)
	std::cout << usage << std::endl;
	else
	{
		std::string arg = argv[1];
		if (arg == "fullInv")
			fullInventory();
		else if (arg == "subject")
			subject();
		else
		{
			std::cerr << "Invalid input.\n" << usage << std::endl;
			return (1);
		}
	}
	return 0;
}
