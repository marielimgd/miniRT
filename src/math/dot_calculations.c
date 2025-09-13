/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:35:40 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/13 19:13:27 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_product(t_vector *a, t_vector *b)
{
	double	result;
	
	// if (a->w != 0 || b->w != 0)
	// 	print_error("Wrong Vector Passed");
	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}

void	dot_cross(t_vector *result, t_vector *a, t_vector *b)
{
	result->x = a->y * b->z - a->z * b->y;
	result->y = a->z * b->x - a->x * b->z;
	result->z = a->x * b->y - a->y * b->x;
	result->w = 0;
}

