/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/06 10:48:40 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Point.hpp"

bool		bsp(Point const a, Point const b, Point const c, Point const point);
static void	checkIfInside(Point const &a, Point const &b, Point const &c, Point const &point);
static void	printCoordinates(Point const &point);
static void	printTriangleCoordinates(Point const &a, Point const &b, Point const &c);

int main(void)
{
	Point a(300, 10);
	Point b(100, 300);
	Point c(500, 300);
	Point p1(250, 250);
	Point p2;
	Point p3(300, 5);
	Point p4(300,10);

	printTriangleCoordinates(a, b, c);
	checkIfInside(a, b, c, p1);
	checkIfInside(a, b, c, p2);
	checkIfInside(a, b, c, p3);
	checkIfInside(a, b, c, p4);
	return (0);
}

static void	printTriangleCoordinates(Point const &a, Point const &b, Point const &c)
{
	std::cout << "A";
	printCoordinates(a);
	std::cout << " B";
	printCoordinates(b);
	std::cout << " C";
	printCoordinates(c);
	std::cout << std::endl;
}

static void	printCoordinates(Point const &point)
{
	std::cout << "(" << point.getX().toInt() << "," << point.getY().toInt() << ")";
}

static void	checkIfInside(Point const &a, Point const &b, Point const &c, Point const &point)
{
	std::cout << "Point";
	printCoordinates(point);
	if (bsp(a, b, c, point))
		std::cout <<" is INSIDE the triangle" << std::endl;
	else
		std::cout << " is OUTSIDE the triangle" << std::endl;
}
