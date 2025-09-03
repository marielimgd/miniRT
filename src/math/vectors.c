/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:10:55 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/02 21:34:01 by jhualves         ###   ########.fr       */
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
	
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	magnitute = get_magnitude(u_vector);
	if(magnitute = 0.0f)
	{
		vector->x = 0.0f;
		vector->y = 0.0f;
		vector->z = 0.0f;
		vector->w = 0.0f;
	}
	else
	{
		vector->x = vector->x/magnitute;
		vector->y = vector->y/magnitute;
		vector->z = vector->z/magnitute;
		vector->w = vector->w/magnitute;
	}
	return (vector);
}

t_vector	*negative_vector(t_vector *vector)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
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
	
	if ((a->w * b->w) != 0)
		printf("ERROR");
	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
	return (result);
}

t_vector	*dot_cross(t_vector *a, t_vector *b)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = a->y * b->z - a->z * b->y;
	result->y = a->z * b->x - a->x * b->z;
	result->z = a->x * b->y - a->y * b->x;
	result->w = 0;
	return (result);
}
