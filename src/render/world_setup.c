/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 19:28:52 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 21:55:28 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*create_world(void)
{
	t_scene	*world;

	world = safe_malloc(sizeof(t_scene), ALLOC_TYPE_SCENE);
	world->lights = NULL;
	world->objects = NULL;
	return (world);
}

/* void	create_default_world(t_scene *world)
{
	t_light		*light;
	t_object	*s1;
	t_object	*s2;

	light = malloc(sizeof(t_light));
	light->origin = create_point(-10, 10, -10);
	light->brightness = 1.0;
	light->color = (t_color){255, 255, 255};
	ft_lstadd_back(&world->lights, ft_lstnew(light));
	s1 = create_sphere();
	s1->material.color = (t_color){(int)(0.8 * 255), (int)(1.0 * 255), (int)(0.6 * 255)};
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;
	ft_lstadd_back(&world->objects, ft_lstnew(s1));
	s2 = create_sphere();
	set_transform(s2, scaling(0.5, 0.5, 0.5));
	ft_lstadd_back(&world->objects, ft_lstnew(s2));
} */

//for testing, replace later
void	create_default_world(t_scene *world)
{
	t_light		*light;
	t_object	*s1;
	t_object	*s2;

	// The light source
	light = malloc(sizeof(t_light));
	light->origin = create_point(-10, 10, -10);
	light->brightness = 1.0;
	light->color = (t_color){255, 255, 255};
	ft_lstadd_back(&world->lights, ft_lstnew(light));
	
	// The large, outer sphere
	s1 = create_sphere();
	s1->material.color = (t_color){(int)(0.8 * 255), (int)(1.0 * 255), (int)(0.6 * 255)};
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;
	ft_lstadd_back(&world->objects, ft_lstnew(s1));

	// The small, inner sphere
	s2 = create_sphere();
	// Ensure the base material is set before transforming
	s2->material = s1->material; 
	s2->material.color = (t_color){255, 255, 255}; // Give it a default color
	set_transform(s2, scaling(0.5, 0.5, 0.5));
	ft_lstadd_back(&world->objects, ft_lstnew(s2));
}