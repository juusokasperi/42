/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/05 20:28:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Point.hpp"

bool		bsp(Point const a, Point const b, Point const c, Point const point);
static void	checkIfInside(Point const &a, Point const &b, Point const &c, Point const &point);

int main(void)
{
	Point a(300, 10);
	Point b(100, 300);
	Point c(500, 300);
	Point p1(250, 250);
	Point p2;
	Point p3(300, 5);
	Point p4(300,10);

	std::cout	<< "A" << a << " B" << b << " C" << c << std::endl;
	checkIfInside(a, b, c, p1);
	checkIfInside(a, b, c, p2);
	checkIfInside(a, b, c, p3);
	checkIfInside(a, b, c, p4);
	Point zero(0, 0);
	std::cout	<< "\nA" << zero << " B" << zero << " C" << zero << std::endl;
	checkIfInside(zero, zero, zero, p1);
	checkIfInside(zero, zero, zero, zero);
	return (0);
}

static void	checkIfInside(Point const &a, Point const &b, Point const &c, Point const &point)
{
	std::cout << "Point" << point;
	if (bsp(a, b, c, point))
		std::cout <<" is INSIDE the triangle" << std::endl;
	else
		std::cout << " is OUTSIDE the triangle" << std::endl;
}
