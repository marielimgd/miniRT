/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:27:57 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:27:57 by jhualves         ###   ########.fr       */
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
	t_color		ambient;
	t_list		*current_light;
	bool		is_in_shadow;

	ambient = scale_color(multiply_color(comps->object->material.color,
				world->ambient_color),
			comps->object->material.ambient * world->ambient_light);
	final_color = ambient;
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
