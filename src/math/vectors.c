/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:10:55 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/08 18:06:10 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	get_magnitude(t_vector *vector)
{
	double	result;
	double	x;
	double	y;
	double	z;
	double	w;

	x = vector->x;
	y = vector->y;
	z = vector->z;
	w = vector->w;
	result = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	return (result);
}

t_vector	*normalization(t_vector *u_vector)
{
	double	magnitute;
	t_vector	*vector;
	

	vector = safe_malloc(sizeof(t_vector), 0);
	if (!vector)
		return (NULL);
	magnitute = get_magnitude(u_vector);
	if(magnitute == 0.0f)
	{
		vector->x = 0.0f;
		vector->y = 0.0f;
		vector->z = 0.0f;
	}
	else
	{
		vector->x = u_vector->x/magnitute;
		vector->y = u_vector->y/magnitute;
		vector->z = u_vector->z/magnitute;	
	}
	vector->w = u_vector->w;
	return (vector);
}

t_vector	*negative_vector(t_vector *vector)
{
	t_vector	*result;

	result = safe_malloc(sizeof(t_vector), 0);
	if (!result)
		return (NULL);
	result->x = - vector->x;
	result->y = - vector->y;
	result->z = - vector->z;
	result->w = 0;
	return (result);
}

double	dot_product(t_vector *a, t_vector *b)
{
	double	result;
	
	// if ((a->w * b->w) != 0)
	// 	print_error("Wrong Vector Passed");
	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}

t_vector	*dot_cross(t_vector *a, t_vector *b)
{
	t_vector	*result;
	
	result = safe_malloc(sizeof(t_vector), 0);
	if (!result)
		return (NULL);
	result->x = a->y * b->z - a->z * b->y;
	result->y = a->z * b->x - a->x * b->z;
	result->z = a->x * b->y - a->y * b->x;
	result->w = 0;
	return (result);
}
