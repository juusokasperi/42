/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:44:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/28 15:55:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLECLASS_HPP
# define SIMPLECLASS_HPP

# include <iostream>

class SimpleClass {
	private:
		std::string name;
		int			val;
	public:
		SimpleClass(std::string name, int val);
		~SimpleClass();
		void		print();
};

#endif /* SIMPLECASS */
