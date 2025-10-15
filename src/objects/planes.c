/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:49:29 by marieli           #+#    #+#             */
/*   Updated: 2025/10/15 18:44:04 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*create_plane(void)
{
	t_object	*plane;

	plane = safe_malloc(sizeof(t_object), ALLOC_TYPE_OBJECT);
	plane->type = PLANE;
	plane->transform = identity_matrix();
	plane->inverse_transform = inverse_matrix(plane->transform);
	plane->transpose_inverse_transform = transpose_matrix(plane->inverse_transform);
	return (plane);
}

#include "minirt.h"

t_intersection_list	intersect_plane(t_object *plane, t_ray ray)
{
	t_intersection_list	intersections;
	double				t;
	t_ray				transformed_ray;

	transformed_ray = transform(ray, plane->inverse_transform);
	if (fabs(transformed_ray.direction.y) < EPSILON)
	{
		intersections.count = 0;
		intersections.intersections = NULL; 
		return (intersections);
	}
	t = -transformed_ray.origin.y / transformed_ray.direction.y;
	intersections.count = 1;
	intersections.capacity = 1;
	intersections.intersections = safe_malloc(sizeof(t_intersection),
			ALLOC_TYPE_GENERIC);
	intersections.intersections[0] = create_intersection(t, plane);
	return (intersections);
}
