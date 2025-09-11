/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:41:51 by marieli           #+#    #+#             */
/*   Updated: 2025/09/11 20:42:37 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	simple_rand(void)
{
	static unsigned int	seed;
    
    seed = 0xDEADBEEF;

	seed = (1103515245 * seed + 12345);
	return ((unsigned int)(seed / 65536) % 32768);
}
