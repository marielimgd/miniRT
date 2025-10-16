/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:55:10 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 13:51:25 by mmariano         ###   ########.fr       */
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
	if (s->inverse_transform)
		free_matrix(s->inverse_transform);
	s->inverse_transform = inverse_matrix(s->transform);
	if (s->transpose_inverse_transform)
		free_matrix(s->transpose_inverse_transform);
	s->transpose_inverse_transform = transpose_matrix(s->inverse_transform);
}

