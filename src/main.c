/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/13 17:21:43 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static void	init_scene(t_scene *scene)
{
	scene->ambient_light = 0.1;
	scene->has_ambient = true;
	scene->ambient_color = (t_color){255, 255, 255};
	scene->lights = NULL;
	scene->objects = NULL;
} */

/* int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		parse_error("Usage: ./miniRT <scene.rt>");
	init_scene(&scene);
	parse_scene(argv[1], &scene);
	init_window(&scene);
	render_scene(&scene);
	mlx_loop(scene.mlx.mlx_ptr);
	free_all();
	return (0);
} */

/* int	main(void)
{
	t_scene		world;
	t_vector	from;
	t_vector	to;
	t_vector	up;

	init_scene(&world);
	create_final_scene_world(&world);
	camera_init(&world.camera, 600, 300, M_PI / 3);
	from = create_point(0, 1.5, -5);
	to = create_point(0, 1, 0);
	up = create_vector(0, 1, 0);
	free_matrix(world.camera.transform);
	world.camera.transform = view_transform(from, to, up);
	init_window(&world);
	render_scene(&world);
	mlx_loop(world.mlx.mlx_ptr);
	free_scene(&world); //trocar por free_all depois
	return (0);
} */

//----------------------------------------------TEST AREA----------------------------------------

static void	init_scene(t_scene *scene)
{
	scene->ambient_light = 0.1;
	scene->has_ambient = true;
	scene->ambient_color = (t_color){255, 255, 255};
	scene->lights = NULL;
	scene->objects = NULL;
}

int	main(void)
{
	t_scene		world;
	t_vector	from;
	t_vector	to;
	t_vector	up;

	init_scene(&world);
	create_final_scene_world(&world);
	camera_init(&world.camera, 600, 300, M_PI / 3);
	from = create_point(0, 1.5, -5);
	to = create_point(0, 1, 0);
	up = create_vector(0, 1, 0);
	free_matrix(world.camera.transform);
	world.camera.transform = view_transform(from, to, up);
	init_window(&world);
	render_scene(&world);
	mlx_loop(world.mlx.mlx_ptr);
	free_scene(&world);
	return (0);
}