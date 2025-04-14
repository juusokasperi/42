/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:41:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/14 16:19:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/* **************************************** */
/*		0,0		x							*/
/* 			------------------------		*/
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

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	sideAB	= (b.getX() - a.getX()) * (point.getY() - a.getY())
						- (b.getY() - a.getY()) * (point.getX() - a.getX());
	Fixed	sideBC	= (c.getX() - b.getX()) * (point.getY() - b.getY())
						- (c.getY() - b.getY()) * (point.getX() - b.getX());
	Fixed	sideCA	= (a.getX() - c.getX()) * (point.getY() - c.getY())
						- (a.getY() - c.getY()) * (point.getX() - c.getX());
	bool	allPositive	= (sideAB > 0) && (sideBC > 0) && (sideCA > 0);
	bool	allNegative = (sideAB < 0) && (sideBC < 0) && (sideCA < 0);

	return (allPositive || allNegative);
}
