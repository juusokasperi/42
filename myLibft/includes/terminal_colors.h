/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_colors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:07:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/27 15:47:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_COLORS_H
# define TERMINAL_COLORS_H

# define TRESET		"\033[0m"
# define BG_RESET	"\033[49m"

// Bright colors
# define BRED		"\033[91m"
# define BGREEN		"\033[92m"
# define BYELLOW	"\033[93m"
# define BBLUE		"\033[94m"
# define BMAGENTA	"\033[95m"
# define BCYAN		"\033[96m"
# define BWHITE		"\033[97m"
# define BG_BGREEN	"\033[102m"
# define BG_BCYAN	"\033[106m"
# define BG_BYELLOW	"\033[103m"
# define BG_BRED	"\033[101m"
// Regular colors
# define TRED		"\033[31m"
# define TGREEN		"\033[32m"
# define TYELLOW	"\033[33m"
# define TBLUE		"\033[34m"
# define TMAGENTA	"\033[35m"
# define TCYAN		"\033[36m"
# define TWHITE		"\033[37m"
# define BG_GREEN	"\033[42m"
# define BG_CYAN	"\033[46m"
# define BG_YELLOW	"\033[43m"
# define BG_RED		"\033[41m"

#endif
