/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:10:26 by marieli           #+#    #+#             */
/*   Updated: 2025/09/15 17:49:30 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sort_intersections(t_intersection_list *list)
{
	int				i;
	int				j;
	t_intersection	temp;

	i = 0;
	while (i < list->count - 1)
	{
		j = 0;
		while (j < list->count - i - 1)
		{
			if (list->intersections[j].t > list->intersections[j + 1].t)
			{
				temp = list->intersections[j];
				list->intersections[j] = list->intersections[j + 1];
				list->intersections[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

t_intersection_list	intersect_world(t_scene *scene, t_ray ray)
{
	t_list					*current_obj;
	t_intersection_list		all_intersections;
	t_intersection_list		obj_hits;
	int						i;

	all_intersections.count = 0;
	current_obj = scene->objects;
	while (current_obj)
	{
		if (((t_object *)current_obj->data)->type == SPHERE)
			obj_hits = intersect_sphere(current_obj->data, ray);
		else if (((t_object *)current_obj->data)->type == PLANE)
			obj_hits = intersect_plane(current_obj->data, ray);
		else
			obj_hits.count = 0; //add cylinder later

		i = 0;
		while (i < obj_hits.count && all_intersections.count < 10)
			all_intersections.intersections[all_intersections.count++] = obj_hits.intersections[i++];
		
		current_obj = current_obj->next;
	}
	sort_intersections(&all_intersections);
	return (all_intersections);
}

static bool is_shadowed(t_scene *scene, t_vector point, t_light *light)
{
	t_vector				v;
	double					distance;
	t_vector				direction;
	t_ray					shadow_ray;
	t_intersection_list		intersections;
	t_intersection			*hit;

	subtract_tuples(&v, &light->origin, &point);
	distance = get_magnitude(&v);
	normalization(&direction, &v);

	shadow_ray = create_ray(point, direction);
	
	intersections = intersect_world(scene, shadow_ray);
	hit = find_hit(&intersections);

	if (hit !=NULL && hit->t < distance)
		return(true);
	return(false);
}

t_color	shade_hit(t_scene *world, t_comps *comps)
{
	t_color		final_color;
	t_list		*current_light;
	bool 		is_in_shadow;
	
	final_color = (t_color){0, 0, 0};
	current_light = world->lights;
	while (current_light)
	{
		is_in_shadow = is_shadowed(world, comps->over_point, current_light->data);
		final_color = add_color(final_color, 
			lighting(comps->object->material, current_light->data, comps, is_in_shadow));
		current_light = current_light->next;
	}
	return (final_color);
}
