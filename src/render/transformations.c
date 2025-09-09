/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:55:10 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/08 17:25:46 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	transform(t_ray ray, t_matrix *m)
{
	t_ray	new_ray;

	new_ray.origin = multiply_matrix_by_tuple(m, ray.origin);
	new_ray.direction = multiply_matrix_by_tuple(m, ray.direction);
	return (new_ray);
}


void	set_transform(t_object *s, t_matrix *t)
{
	if (s->transform)
		free_matrix(s->transform);
	s->transform = t;
}

t_matrix	*rotation_x(double radians)
{
	t_matrix	*m;

	m = identity_matrix();
	m->matrix[1][1] = cos(radians);
	m->matrix[1][2] = -sin(radians);
	m->matrix[2][1] = sin(radians);
	m->matrix[2][2] = cos(radians);
	return (m);
}

t_matrix	*rotation_y(double radians)
{
	t_matrix	*m;

	m = identity_matrix();
	m->matrix[0][0] = cos(radians);
	m->matrix[0][2] = sin(radians);
	m->matrix[2][0] = -sin(radians);
	m->matrix[2][2] = cos(radians);
	return (m);
}

t_matrix	*rotation_z(double radians)
{
	t_matrix	*m;

	m = identity_matrix();
	m->matrix[0][0] = cos(radians);
	m->matrix[0][1] = -sin(radians);
	m->matrix[1][0] = sin(radians);
	m->matrix[1][1] = cos(radians);
	return (m);
}
