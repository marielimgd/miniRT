/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:58:31 by marieli           #+#    #+#             */
/*   Updated: 2025/10/16 19:25:35 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_at(t_scene *world, t_ray ray)
{
	t_intersection_list	intersections;
	t_intersection		*hit;
	t_comps				comps;
	t_color				result;

	intersections = intersect_world(world, ray);
	hit = find_hit(&intersections);
	if (hit == NULL)
	{
		free(intersections.intersections);
		return ((t_color){0, 0, 0});
	}
	prepare_computations(&comps, hit, &ray);
	result = shade_hit(world, &comps);
	free(intersections.intersections);
	return (result);
}
