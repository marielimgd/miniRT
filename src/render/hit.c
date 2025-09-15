/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:20:10 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/15 18:20:20 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	is_shadowed(t_scene *scene, t_vector point, t_light *light)
{
	t_vector			v;
	double				distance;
	t_vector			direction;
	t_ray				shadow_ray;
	t_intersection_list	intersections;
	t_intersection		*hit;

	subtract_tuples(&v, &light->origin, &point);
	distance = get_magnitude(&v);
	normalization(&direction, &v);
	shadow_ray = create_ray(point, direction);
	intersections = intersect_world(scene, shadow_ray);
	hit = find_hit(&intersections);
	if (hit != NULL && hit->t < distance)
	{
		free(intersections.intersections);
		return (true);
	}
	free(intersections.intersections);
	return (false);
}

t_color	shade_hit(t_scene *world, t_comps *comps)
{
	t_color		final_color;
	t_list		*current_light;
	bool		is_in_shadow;

	final_color = (t_color){0, 0, 0};
	current_light = world->lights;
	while (current_light)
	{
		is_in_shadow = is_shadowed(world, comps->over_point,
				current_light->data);
		final_color = add_color(final_color,
				lighting(comps->object->material, current_light->data, comps,
					is_in_shadow));
		current_light = current_light->next;
	}
	return (final_color);
}
