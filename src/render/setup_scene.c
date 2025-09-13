/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:11:21 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 22:12:52 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	create_floor(t_scene *world)
{
	t_object	*floor;

	floor = create_sphere();
	set_transform(floor, scaling(10, 0.01, 10));
	floor->material.color = (t_color){255, (int)(0.9 * 255), (int)(0.9 * 255)};
	floor->material.specular = 0;
	ft_lstadd_back(&world->objects, ft_lstnew(floor));
}

static void	create_walls(t_scene *world)
{
	t_object	*wall;
	t_matrix	*temp1;
	t_matrix	*temp2;
	t_material	floor_mat;

	floor_mat = ((t_object *)world->objects->data)->material;
	wall = create_sphere();
	temp1 = matrix_product(rotation_y(-M_PI / 4), rotation_x(M_PI / 2));
	temp2 = matrix_product(temp1, scaling(10, 0.01, 10));
	set_transform(wall, matrix_product(translation(0, 0, 5), temp2));
	wall->material = floor_mat;
	ft_lstadd_back(&world->objects, ft_lstnew(wall));
	free_matrix(temp1);
	free_matrix(temp2);
	wall = create_sphere();
	temp1 = matrix_product(rotation_y(M_PI / 4), rotation_x(M_PI / 2));
	temp2 = matrix_product(temp1, scaling(10, 0.01, 10));
	set_transform(wall, matrix_product(translation(0, 0, 5), temp2));
	wall->material = floor_mat;
	ft_lstadd_back(&world->objects, ft_lstnew(wall));
	free_matrix(temp1);
	free_matrix(temp2);
}

static void	create_spheres(t_scene *world)
{
	t_object	*sphere;
	t_matrix	*scale_m;
	t_matrix	*trans_m;

	sphere = create_sphere();
	set_transform(sphere, translation(-0.5, 1, 0.5));
	sphere->material.color = (t_color){(int)(0.1*255), 255, (int)(0.5*255)};
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	ft_lstadd_back(&world->objects, ft_lstnew(sphere));
	sphere = create_sphere();
	trans_m = translation(1.5, 0.5, -0.5);
	scale_m = scaling(0.5, 0.5, 0.5);
	set_transform(sphere, matrix_product(trans_m, scale_m));
	sphere->material.color = (t_color){(int)(0.5*255), 255, (int)(0.1*255)};
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	ft_lstadd_back(&world->objects, ft_lstnew(sphere));
	sphere = create_sphere();
	trans_m = translation(-1.5, 0.33, -0.75);
	scale_m = scaling(0.33, 0.33, 0.33);
	set_transform(sphere, matrix_product(trans_m, scale_m));
	sphere->material.color = (t_color){255, (int)(0.8*255), (int)(0.1*255)};
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	ft_lstadd_back(&world->objects, ft_lstnew(sphere));
}

void	create_final_scene_world(t_scene *world)
{
	create_floor(world);
	create_walls(world);
	create_spheres(world);
	world->lights = ft_lstnew(malloc(sizeof(t_light)));
	*(t_light *)world->lights->data = \
		(t_light){create_point(-10, 10, -10), 1.0, {255, 255, 255}};
}