/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/13 19:03:29 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static void	init_scene(t_scene *scene)
{
	scene->ambient_light = -1.0;
	scene->has_ambient = false;
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

//----------------------------------------------TEST AREA----------------------------------------

/* In src/main.c */

#include "minirt.h"

int	main(void)
{
	t_scene		*world;
	t_vector	from;
	t_vector	to;
	t_vector	up;

	// 1. Create the world struct
	world = create_world();
	
	// 2. POPULATE THE WORLD with test objects and lights
	create_default_world(world);

	// 3. Initialize the camera's settings
	camera_init(&world->camera, WIDTH, HEIGHT, M_PI / 3.0);

	// 4. Define the camera's position and orientation
	from = create_point(0, 1.5, -5);
	to = create_point(0, 1, 0);
	up = create_vector(0, 1, 0);

	// 5. Create the view matrix and assign it to the camera
	world->camera.transform = view_transform(from, to, up);
	
	// 6. INITIALIZE THE WINDOW before rendering
	init_window(world);
	
	// 7. Render the scene
	render_scene(world);
	mlx_loop(world->mlx.mlx_ptr);

	// 8. Use your master cleanup function
	free_all();

	return (0);
}