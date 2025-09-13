/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/12 21:57:35 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

void	subtract_tuples(t_vector *result, t_vector *a, t_vector *b)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	result->w = a->w - b->w;
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

