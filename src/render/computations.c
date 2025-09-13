/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:06:39 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 20:06:53 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	prepare_computations(t_comps *comps, t_intersection *i, t_ray *ray)
{
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
}
