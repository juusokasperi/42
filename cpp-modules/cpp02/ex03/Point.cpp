/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:08:54 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/05 20:33:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(): _x(Fixed(0)), _y(Fixed(0))
{
}

Point::Point(const float x, const float y): _x(Fixed(x)), _y(Fixed(y))
{
}

Point::Point(const Point &src): _x(src._x), _y(src._y)
{
}

Point::~Point()
{
}

const Fixed	Point::getX(void) const
{
	return (_x);
}

const Fixed	Point::getY(void) const
{
	return (_y);
}

std::ostream& operator<<(std::ostream &os, const Point& point)
{
	os << "(" << point.getX() << "," << point.getY() << ")";
	return (os);
}
