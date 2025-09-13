/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:10:26 by marieli           #+#    #+#             */
/*   Updated: 2025/09/13 19:42:57 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	intersect_world(t_scene *scene, t_ray ray)
{
    t_list				*current_obj_node;
    t_intersection_list	all_intersections;
    t_intersection_list	obj_hits;
    t_intersection		*hit;
    int					i;

    all_intersections.count = 0;
    current_obj_node = scene->objects;
    while (current_obj_node)
    {
        t_object *obj = (t_object *)current_obj_node->data;
        if (obj->type == SPHERE)
        {
            obj_hits = intersect_sphere(obj, ray);
            i = 0;
            while (i < obj_hits.count && all_intersections.count < 10)
            {
                all_intersections.intersections[all_intersections.count++] = obj_hits.intersections[i++];
            }
        }
        current_obj_node = current_obj_node->next;
    }
    hit = find_hit(&all_intersections);
    if (hit)
        return (*hit);
    return ((t_intersection){-1, NULL});
}

/* In src/render/world.c */

t_color	shade_hit(t_scene *scene, t_intersection hit, t_ray ray)
{
	t_lighting_data	d;
	t_color			final_color;
	t_list			*current_light_node;

	d.point = ray_position(ray, hit.t);
	d.normalv = normal_at(hit.object, d.point);
	negative_vector(&d.eyev, &ray.direction);
	final_color = scale_color(hit.object->material.color, scene->ambient_light);
	current_light_node = scene->lights;
	while (current_light_node)
	{
		final_color = add_color(final_color,
			lighting(hit.object->material, current_light_node->data, d));
		current_light_node = current_light_node->next;
	}
	return (final_color);
}
