/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:33:45 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

void	add_tuples(t_vector *result, t_vector *vector, t_vector *point)
{
	result->x = vector->x + point->x;
	result->y = vector->y + point->y;
	result->z = vector->z + point->z;
	result->w = vector->w + point->w;
}

void	subtract_tuples(t_vector *result, t_vector *vector, t_vector *point)
{
	result->x = vector->x - point->x;
	result->y = vector->y - point->y;
	result->z = vector->z - point->z;
	result->w = vector->w - point->w;
}

void	scale_tuples_product(t_vector *result, t_vector *vector, double scale)
{
	result->x = vector->x * scale;
	result->y = vector->y * scale;
	result->z = vector->z * scale;
	result->w = vector->w * scale;
}

void	scale_tuples_divison(t_vector *result, t_vector *vector, double scale)
{
	result->x = vector->x / scale;
	result->y = vector->y / scale;
	result->z = vector->z / scale;
	result->w = vector->w / scale;
}
