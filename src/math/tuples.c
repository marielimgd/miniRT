/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/08 19:39:59 by mmariano         ###   ########.fr       */
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

t_vector	*add_tuples(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x + point->x;
	result->y = vector->y + point->y;
	result->z = vector->z + point->z;
	result->w = vector->w + point->w;
	return (result);
}

t_vector	*subtract_tuples(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x - point->x;
	result->y = vector->y - point->y;
	result->z = vector->z - point->z;
	result->w = vector->w - point->w;
	return (result);
}

t_vector	*scale_tuples_product(t_vector *vector, double scale)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x * scale;
	result->y = vector->y * scale;
	result->z = vector->z * scale;
	result->w = vector->w * scale;
	return (result);
}

t_vector	*scale_tuples_divison(t_vector *vector, double scale)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x / scale;
	result->y = vector->y / scale;
	result->z = vector->z / scale;
	result->w = vector->w / scale;
	return (result);
}

