/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:10:26 by marieli           #+#    #+#             */
/*   Updated: 2025/10/23 12:22:24 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

static void	add_intersection(t_intersection_list *list, t_intersection i)
{
	if (list->count == list->capacity)
	{
		list->capacity *= 2;
		list->intersections = realloc(list->intersections,
				list->capacity * sizeof(t_intersection));
		if (!list->intersections)
			print_error("Failed to reallocate intersections");
	}
	list->intersections[list->count++] = i;
}

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

static void	intersect_object_and_append(t_object *obj, t_ray ray,
		t_intersection_list *list)
{
	t_intersection_list	obj_hits;
	int					i;

	obj_hits.count = 0;
	obj_hits.intersections = NULL;
	if (obj->type == SPHERE)
		obj_hits = intersect_sphere(obj, ray);
	else if (obj->type == PLANE)
		obj_hits = intersect_plane(obj, ray);
	i = 0;
	while (i < obj_hits.count)
	{
		add_intersection(list, obj_hits.intersections[i]);
		i++;
	}
	if (obj_hits.intersections)
		free(obj_hits.intersections);
}

t_intersection_list	intersect_world(t_scene *scene, t_ray ray)
{
	t_list				*current_obj;
	t_intersection_list	all_intersections;

	all_intersections.count = 0;
	all_intersections.capacity = 10;
	all_intersections.intersections = malloc(all_intersections.capacity
			* sizeof(t_intersection));
	current_obj = scene->objects;
	while (current_obj)
	{
		intersect_object_and_append(current_obj->data, ray, &all_intersections);
		current_obj = current_obj->next;
	}
	sort_intersections(&all_intersections);
	return (all_intersections);
}

t_scene	*create_world(void)
{
	t_scene	*world;

	world = safe_malloc(sizeof(t_scene), ALLOC_TYPE_SCENE);
	world->lights = NULL;
	world->objects = NULL;
	world->selected_object = NULL;
	world->has_ambient = false;
	world->has_camera = false;
	world->translation_mode = false;
	world->rotation_mode = false;
	return (world);
}
