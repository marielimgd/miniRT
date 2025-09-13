/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:03:43 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 21:05:13 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_intersection_list	intersect_plane(t_object *plane, t_ray ray)
{
	t_intersection_list	intersections;
	double				t;
	double				denominator;

	(void)plane;
	intersections.count = 0;
	denominator = dot_product(&ray.direction, &plane->prop.plane.normal);
	if (fabs(denominator) < EPSILON)
		return (intersections);
	t = -dot_product(&ray.origin, &plane->prop.plane.normal)
		/ denominator;
	if (t > 0)
	{
		intersections.intersections[0] = create_intersection(t, plane);
		intersections.count = 1;
	}
	return (intersections);
}

t_vector	normal_at_plane(t_object *plane, t_vector world_point)
{
	(void)world_point;
	
	return (plane->prop.plane.normal);
}