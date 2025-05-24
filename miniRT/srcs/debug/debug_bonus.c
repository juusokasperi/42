/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:48 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/22 10:33:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_bonus.h"

void	print_threading_info(int thread_count)
{
	printf("Threading information:\n");
	printf("  - Thread count: %d\n", thread_count);
	printf("  - Threading approach: Tiles (%dx%d pixels)\n", TILE_SIZE,
		TILE_SIZE);
}
