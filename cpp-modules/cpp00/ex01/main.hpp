/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:19:50 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/01 17:50:49 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

# include <string>
# include <iomanip>
# include <iostream>
# include "PhoneBook.hpp"

# define TMAGENTA		"\033[95m"
# define TYELLOW		"\033[93m"
# define TRESET			"\033[0m"

void	add_contact(PhoneBook *phoneBook);
void	search_contact(PhoneBook *phoneBook);

#endif /* MAIN_HPP */
