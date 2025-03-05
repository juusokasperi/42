/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:41:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/04 17:13:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/* **************************************** */
/*		0,0		x							*/
/* 			 ------------------------		*/
/*		y	|			  B					*/
/* 			|			  /\				*/
/*			|			 /  \				*/
/*			|			/	 \				*/
/*			|		   /	  \				*/
/*			|		  /	  *	   \			*/
/*			|		 /		    \			*/
/*			|		/____________\			*/
/*				  A	 			  C			*/
/* **************************************** */

static Fixed	abs(Fixed x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

static Fixed	area(Point const a, Point const b, Point const c)
{
	return (((a.getX() * ( b.getY() - c.getY())) +
			(b.getX() * ( c.getY() - a.getY())) +
			(c.getX() * (a.getY() - b.getY()))) / 2 );
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	abcArea = abs(area(a, b, c));
	Fixed	pabArea = abs(area(point, a, b));
	Fixed	pbcArea = abs(area(point, b, c));
	Fixed	pcaArea = abs(area(point, c, a));

	if (pabArea == 0 || pbcArea == 0 || pcaArea == 0)
		return (false);
	return (abcArea == pabArea + pbcArea + pcaArea);
}
