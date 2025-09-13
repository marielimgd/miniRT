/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:10:26 by marieli           #+#    #+#             */
/*   Updated: 2025/09/13 20:50:54 by marieli          ###   ########.fr       */
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
	t_list				*current_obj;
	t_intersection_list	all_intersections;
	t_intersection_list	obj_hits;
	int					i;

	all_intersections.count = 0;
	current_obj = scene->objects;
	while (current_obj)
	{
		if (((t_object *)current_obj->data)->type == SPHERE)
			obj_hits = intersect_sphere(current_obj->data, ray);
		else if (((t_object *)current_obj->data)->type == PLANE)
			obj_hits = intersect_plane(current_obj->data, ray);
		else
			obj_hits.count = 0; //for cylinder later

		i = 0;
		while (i < obj_hits.count && all_intersections.count < 10)
			all_intersections.intersections[all_intersections.count++] = obj_hits.intersections[i++];
		
		current_obj = current_obj->next;
	}
	sort_intersections(&all_intersections);
	return (all_intersections);
}

t_color	shade_hit(t_scene *world, t_comps *comps)
{
	t_color		final_color;
	t_list		*current_light;

	final_color = (t_color){0, 0, 0};
	current_light = world->lights;
	while (current_light)
	{
		final_color = add_color(final_color, 
			lighting(comps->object->material, current_light->data, comps));
		current_light = current_light->next;
	}
	return (final_color);
}

