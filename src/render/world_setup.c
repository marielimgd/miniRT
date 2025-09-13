/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:49 by marieli           #+#    #+#             */
/*   Updated: 2025/09/13 18:44:18 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*create_world(void)
{
	t_scene	*world;

	world = malloc(sizeof(t_scene));
	if (!world)
		print_error("Failed to allocate world");
	world->lights = NULL;
	world->objects = NULL;
	world->has_ambient = false;
	return (world);
}

// ONLY FOR TESTING: Creates a default world with a light source and two spheres.
void	create_default_world(t_scene *world)
{
	t_light		*light;
	t_object	*sphere1;
	t_object	*sphere2;

	light = malloc(sizeof(t_light));
	if (!light)
		print_error("Failed to allocate light");
	light->origin = create_point(-10, 10, -10);
	light->brightness = 1.0;
	light->color = (t_color){255, 255, 255};
	ft_lstadd_back(&world->lights, ft_lstnew(light));

	sphere1 = create_sphere();
	sphere1->material.color = (t_color){(int)(0.8 * 255), 255, (int)(0.6 * 255)};
	sphere1->material.diffuse = 0.7;
	sphere1->material.specular = 0.2;
	ft_lstadd_back(&world->objects, ft_lstnew(sphere1));
    
	sphere2 = create_sphere();
	set_transform(sphere2, scaling(0.5, 0.5, 0.5));
	ft_lstadd_back(&world->objects, ft_lstnew(sphere2));
}