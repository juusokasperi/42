/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:35:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/25 09:56:03 by jrinta-          ###   ########.fr       */
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

	AMateria* iceBolt = src->createMateria("ice");
	AMateria* cure = src->createMateria("cure");
	AMateria* cure2 = src->createMateria("cure");
	AMateria* ice = src->createMateria("ice");
	AMateria* snow = src->createMateria("snow");
	AMateria* kissa = src->createMateria("ice");
	std::cout << std::endl;

	*cure2 = *cure;
	*ice = *iceBolt;
	std::cout << std::endl;

	//	Inv is still empty;
	joe->unequip(0);
	joe->unequip(1);
	joe->unequip(2);
	joe->unequip(3);
	//	Invalid index:
	joe->unequip(4);
	std::cout << std::endl;
	//	Equipping the materias
	joe->equip(iceBolt);
	joe->equip(cure);
	joe->equip(ice);
	joe->equip(cure2);
	//	Invalid materia:
	joe->equip(snow);
	//	Inv full
	joe->equip(kissa);
	//	Using all the materias, which are;
	//	Ice, Cure, Ice, Cure
	for (int i = 0; i < 4; ++i)
		joe->use(i, *joe);
	//	Invalid index:
	joe->use(4, *joe);

	delete (kissa);
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

static void	deepCopy()
{
	std::cout << "\033[0;32m *** TESTING DEEP COPY TEST ***\033[0m" << std::endl;

	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	Character	matt("Matt");
	Character	don("Don");
	std::cout << std::endl;

	matt.equip(src->createMateria("ice"));
	matt.equip(src->createMateria("ice"));
	don.equip(src->createMateria("cure"));
	don.equip(src->createMateria("cure"));
	std::cout << std::endl;
	// Don uses "cure"
	don.use(0, matt);

	std::cout << std::endl;
	// Don becomes Matt -> the two cures are destroyed and the two ices from original Matt's
	// inv are cloned to new Matt (old Don)
	don = matt;
	// So now Don (now Matt) uses ice, then we unequip that, try using it to
	// make sure it was destroyed, and then try using slot 0 from original Matt to see
	// that the unequip of Don didn't affect Matt.
	don.use(0, matt);
	don.unequip(0);
	don.use(0, matt);
	matt.use(0, don);
	delete (src);
}

int	main(int argc, char **argv)
{
	std::string usage = "Usage: " + (std::string)argv[0] + " <inv>/<subject>/<deep>";
	if (argc != 2)
	std::cout << usage << std::endl;
	else
	{
		std::string arg = argv[1];
		if (arg == "inv")
			fullInventory();
		else if (arg == "subject")
			subject();
		else if (arg == "deep")
			deepCopy();
		else
		{
			std::cerr << "Invalid input.\n" << usage << std::endl;
			return (1);
		}
	}
	return 0;
}
