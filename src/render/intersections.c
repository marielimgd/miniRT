/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:28:07 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 17:33:22 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	create_intersection(double t, t_object *obj)
{
	t_intersection	i;

	i.t = t;
	i.object = obj;
	return(i);
}

t_intersection_list	create_intersections_list(int count, ...)
{
	t_intersection_list	list;
	va_list				args;
	int					i;

	list.count = count;
	list.capacity = count;
	list.intersections = malloc(count * sizeof(t_intersection));
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		list.intersections[i] = va_arg(args, t_intersection);
		i++;
	}
	va_end(args);
	return (list);
}

t_intersection	intersect_object(t_object *object, t_ray ray)
{
	t_intersection 			empty;
	t_intersection_list 	sphere_list;

	if (object->type == SPHERE)
	{
		sphere_list = intersect_sphere(object, ray);
		if (sphere_list.count > 0)
			return (sphere_list.intersections[0]);
	}

	empty.t = -1;
	empty.object = NULL;
	return (empty);
}

t_intersection		*find_hit(t_intersection_list *list)
{
	int				i;
	t_intersection	*closest_hit;

	closest_hit = NULL;
	i = 0;
	while(i < list->count)
	{
		if (list->intersections[i].t >= 0)
		{
			if (closest_hit == NULL)
				closest_hit = &list->intersections[i];
			else if (list->intersections[i].t < closest_hit->t)
				closest_hit = &list->intersections[i];
		}
		i++;
	}
	return(closest_hit);
}
