/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:48:40 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/29 09:54:50by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.tpp"
#include <iostream>

static void	test_str(void)
{
	std::cout << "\033[0;33m*** TEST STRING ARRAY***\033[0m\n";
	Array<std::string> strArray;
	Array<std::string> strArray2(10);

	std::cout << "\033[0;32m··\033[0m Default constructor was called for first array, size is " << strArray.size() << "\n";
	std::cout <<  "\033[0;32m··\033[0m Second array size is " << strArray2.size() << "\n";
	strArray = strArray2;
	std::cout << "\033[0;32m··\033[0m Copy assignment operator called for strArray = strArray2, so strArray.size is " << strArray.size() << "\n";

	for (unsigned int i = 0; i < strArray.size(); i++)
		strArray[i] = "foo[" + std::to_string(i) + "]";
	for (unsigned int i = 0; i < strArray2.size(); i++)
		strArray2[i] = "bar[" + std::to_string(i) + "]";

	std::cout << "\n";
	for (unsigned int i = 0; i < strArray.size(); i++)
		std::cout << strArray[i] << "\n";
	for (unsigned int i = 0; i < strArray2.size(); i++)
		std::cout << strArray2[i] << "\n";
	std::cout << "\n";
	strArray = std::move(strArray2);
	std::cout <<  "\033[0;32m··\033[0m Moving strArray2 to strArray so second array size is " << strArray2.size() << "\n";
	std::cout <<  "\033[0;32m··\033[0m Printing strarray (now bar instead of foo) " << strArray2.size() << "\n";
	for (unsigned int i = 0; i < strArray.size(); i++)
		std::cout << strArray[i] << "\n";
	try {
		std::cout <<  "\n\033[0;32m··\033[0m Trying to access strArray2\n";
		std::cout << strArray2[0] << "\n";
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	std::cout << "\n";
}

static void	test_float(void)
{
	std::cout << "\033[0;33m*** TEST FLOAT ARRAY***\033[0m\n";
	Array<float> array(10);
	Array<float> array2(array);

	std::cout << "\033[0;32m··\033[0m First array size is " << array.size() << "\n";
	std::cout <<  "\033[0;32m··\033[0m Second array created w/ copy, size is " << array2.size() << "\n";

	for (unsigned int i = 0; i < array.size(); ++i)
		array[i] = 0.0f + i;;
	for (unsigned int i = 0; i < array2.size(); ++i)
		array2[i] = 0.5f + i;

	for (unsigned int i = 0; i < array.size(); ++i)
		std::cout << "Array [" << i << "] " << array[i] << "\n";
	for (unsigned int i = 0; i < array2.size(); ++i)
		std::cout << "Array2[" << i << "] " << array2[i] << "\n";
	std::cout << "\n";
	array = std::move(array2);
	std::cout <<  "\033[0;32m··\033[0m Moving array2 to array so second array size is " << array2.size() << "\n";
	std::cout <<  "\033[0;32m··\033[0m Printing contents of array\n";
	for (int i = 0; i < 10; i++)
		std::cout << array[i] << "\n";
	std::cout << "\n";
	try { 
		std::cout << "\033[0;32m··\033[0m Trying to access array2\n";
		std::cout << array2[0] << "\n";
	} catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n\n";
	}

	Array<float> array3(std::move(array));
	std::cout <<  "\033[0;32m··\033[0m Moving array to array3 so first array size is " << array.size() << "\n";
	for (unsigned int i = 0; i < array3.size(); ++i)
		std::cout << array3[i] << "\n";
	try {
		std::cout << "\n\033[0;32m··\033[0m Trying to reach index 10 from array3 (out of bounds)\n";
		std::cout << array3[10] << "\n";
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n\n";
	}
	try { 
		std::cout << "\033[0;32m··\033[0m Trying to access array1\n";
		std::cout << array[0] << "\n";
	} catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}
	std::cout << "\n";
}

static void test_const(void)
{
	std::cout << "\033[0;33m*** TEST CONST INT ARRAY***\033[0m\n";
	Array<int> array(5);

	for (unsigned int i = 0; i < array.size(); ++i)
		array[i] = i;
	const Array<int> constArray = array;
	for (unsigned int i = 0; i < array.size(); ++i)
		array[i] = i * 2;
	
	for (unsigned int i = 0; i < array.size(); ++i)
		std::cout << "     array[" << i << "]: " << array[i] << "\n";
	for (unsigned int i = 0; i < constArray.size(); ++i)
		std::cout << "constArray[" << i << "]: " << constArray[i] << "\n";
	std::cout << "\n";
}

static void test_initialization(void)
{
	std::cout << "\033[0;33m*** TEST INITALIZATION INT ARRAY***\033[0m\n";
	std::cout <<  "\033[0;32m··\033[0m All integers should be initialized to 0 by default\n";
	Array<int> array(5);

	for (unsigned int i = 0; i < array.size(); ++i)
		std::cout << "array[" << i << "] " << array[i] << "\n";
	std::cout << "\n";
}

static void test_empty(void)
{
	std::cout << "\033[0;33m***TEST SIZE 0***\033[0m\n";
	Array<int> array(0);
	std::cout << "\033[0;32m··\033[0m Array size is " << array.size() << "\n";
	try {
		std::cout << "Trying to access array[0]\n";
		std::cout << array[0] << "\n";
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	std::cout << "\n";
}

int	main(void)
{
	test_str();
	test_float();
	test_const();
	test_initialization();
	test_empty();
	return (0);
}
