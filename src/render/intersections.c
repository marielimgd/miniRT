/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:28:07 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/04 19:30:43 by mmariano         ###   ########.fr       */
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
t_intersect_list	create_intersections_list(int count, ...)
{
	t_intersect_list	list;
	va_list				args;
	int					i;
	
	list.count = count;
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		list.intersections[i] = va_arg(args, t_intersection);
		i++;
	}
	va_end(args);
	return(list);
}
t_intersection	intersect_object(t_object *object, t_ray ray)
{
	t_intersection 		empty;
	t_intersect_list 	sphere_list;
	
	if (object->type == SPHERE)
	{
		sphere_list = intersect_sphere(object, ray);
		if (sphere_list.count > 0)
			return (sphere_list.intersections[0]);
	}
	// if (object->type == PLANE)
	// {
	// 	t_intersect_list plane_list = intersect_plane(object, ray);
	// 	if (plane_list.count > 0)
	// 		return plane_list.intersections[0];
	// }
	// if (object->type == CYLINDER)
	// {
	// 	t_intersect_list cylinder_list = intersect_cylinder(object, ray);
	// 	if (cylinder_list.count > 0)
	// 		return cylinder_list.intersections[0];
	// }
	
	empty.t = -1;
	empty.object = NULL;
	return (empty);
}
