/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:23:31 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:23:31 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_magnitude(t_vector *vector)
{
	double	result;
	double	x;
	double	y;
	double	z;

	x = vector->x;
	y = vector->y;
	z = vector->z;
	result = sqrt((x * x) + (y * y) + (z * z));
	return (result);
}

void	normalization(t_vector *result, t_vector *u_vector)
{
	double	magnitute;

	magnitute = get_magnitude(u_vector);
	if (magnitute < EPSILON)
	{
		result->x = 0.0f;
		result->y = 0.0f;
		result->z = 0.0f;
	}
	else
	{
		result->x = u_vector->x / magnitute;
		result->y = u_vector->y / magnitute;
		result->z = u_vector->z / magnitute;
	}
	result->w = u_vector->w;
}

void	negative_vector(t_vector *result, t_vector *vector)
{
	result->x = -vector->x;
	result->y = -vector->y;
	result->z = -vector->z;
	result->w = -vector->w;
}

bool	are_vectors_equal(t_vector a, t_vector b)
{
	bool	result;

	if (is_equal(a.x, b.x) \
	&& is_equal(a.y, b.y) \
	&& is_equal(a.z, b.z) \
	&& is_equal(a.w, b.w))
	{
		result = true;
	}
	else
		result = false;
	return (result);
}
