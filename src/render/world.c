/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:10:26 by marieli           #+#    #+#             */
/*   Updated: 2025/09/12 17:15:24 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_intersection	intersect_world(t_scene *scene, t_ray ray)
{
    t_list				*objects;
    t_intersection_list	intersections;
    t_intersection_list	obj_intersections;
    t_intersection		*hit;
    int					i;

    intersections.count = 0;
    objects = scene->objects;
    while (objects)
    {
        if (((t_object *)objects->data)->type == SPHERE) //add other object types later
        {
            obj_intersections = intersect_sphere(objects->data, ray);
            i = 0;
            while (i < obj_intersections.count)
                intersections.intersections[intersections.count++] = obj_intersections.intersections[i++];
        }
        objects = objects->next;
    }
    hit = find_hit(&intersections);
    if (hit)
        return (*hit);
    return ((t_intersection){-1, NULL});
}

t_color	shade_hit(t_scene *scene, t_intersection hit, t_ray ray)
{
	t_lighting_data	    d;
    t_vector		    eyev;
	t_color			    surface_color;
	t_color			    ambient_contribution;

	d.point = ray_position(ray, hit.t);
	d.normalv = normal_at(hit.object, d.point);
	negative_vector(&eyev, &ray.direction);
	d.eyev = eyev;

	if (scene->lights)
		surface_color = lighting(hit.object->material, scene->lights->data, d);
	else
		surface_color = (t_color){0, 0, 0};
	ambient_contribution = scale_color(hit.object->color, scene->ambient_light);
	return (add_color(surface_color, ambient_contribution));
}
