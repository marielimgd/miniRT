/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:00:55 by marieli           #+#    #+#             */
/*   Updated: 2025/09/15 17:15:47 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	prepare_computations(t_comps *comps, t_intersection *i, t_ray *ray)
{
	t_vector		scaled_normal;

	comps->t = i->t;
	comps->object = i->object;
	comps->point = ray_position(*ray, comps->t);
	negative_vector(&comps->eyev, &ray->direction);
	comps->normalv = normal_at(comps->object, comps->point);
	comps->inside = false;
	if (dot_product(&comps->normalv, &comps->eyev) < 0)
	{
		comps->inside = true;
		negative_vector(&comps->normalv, &comps->normalv);
	}
	scale_tuples_product(&scaled_normal, &comps->normalv, EPSILON);
	add_tuples(&comps->over_point, &comps->point, &scaled_normal);
}
