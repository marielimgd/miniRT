/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:58:31 by marieli           #+#    #+#             */
/*   Updated: 2025/09/13 20:04:44 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

t_color	color_at(t_scene *world, t_ray ray)
{
	t_intersection_list	intersections;
	t_intersection		*hit;
	t_comps				comps;

	intersections = intersect_world(world, ray);
	hit = find_hit(&intersections);
	if (hit == NULL)
		return ((t_color){0, 0, 0});
	prepare_computations(&comps, hit, &ray);
	return (shade_hit(world, &comps));
}
