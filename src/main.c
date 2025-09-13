/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 22:26:20 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

 static void	init_scene(t_scene *scene)
{
	scene->ambient_light = 0.1;
	scene->has_ambient = false;
	scene->ambient_color = (t_color){255, 255, 255};
	scene->lights = NULL;
	scene->objects = NULL;
}

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

/* #include "minirt.h"

// init_scene remains the same
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
	t_object	*sphere;

	// 1. Basic scene setup
	init_scene(&world);
	world.lights = ft_lstnew(malloc(sizeof(t_light)));
	*(t_light *)world.lights->data = \
		(t_light){create_point(0, 5, -10), 1.0, {255, 255, 255}};

	// 2. Create ONE simple sphere and place it in front of the camera
	sphere = create_sphere();
	set_transform(sphere, translation(0, 0, 5)); // Place it at z=5
	ft_lstadd_back(&world.objects, ft_lstnew(sphere));

	// 3. Use the simplest possible camera (at origin, looking forward)
	camera_init(&world.camera, 400, 200, M_PI / 2);
	// We DO NOT set a view_transform, so it uses the default identity matrix.
	// This places the camera at (0,0,0) looking toward the -Z direction.

	// 4. Render the simple scene
	init_window(&world);
	render_scene(&world);
	mlx_loop(world.mlx.mlx_ptr);
	free_scene(&world);
	return (0);
} */

static void	create_floor(t_scene *world)
{
	t_object	*floor;

	floor = create_sphere();
	set_transform(floor, scaling(10, 0.01, 10));
	floor->material.color = (t_color){255, (int)(0.9 * 255), (int)(0.9 * 255)};
	floor->material.specular = 0;
	ft_lstadd_back(&world->objects, ft_lstnew(floor));
}
/* static void	create_walls(t_scene *world)
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
} */

#include "minirt.h"

// init_scene, create_floor, and your other scene-building helpers...

/**
 * @brief The main function to render the hardcoded final scene.
 */
int	main(void)
{
	t_scene		world;
	t_vector	from;
	t_vector	to;
	t_vector	up;

	init_scene(&world);

	// Create just the floor and the light source
	create_floor(&world);
	world.lights = ft_lstnew(malloc(sizeof(t_light)));
	*(t_light *)world.lights->data = \
		(t_light){create_point(-10, 10, -10), 1.0, {255, 255, 255}};
	
	// ✅ FIX: Set up a proper camera view
	camera_init(&world.camera, 600, 300, M_PI / 3);
	from = create_point(0, 1.5, -5); // Position the camera above and back
	to = create_point(0, 1, 0);      // Look at a point slightly in front of the origin
	up = create_vector(0, 1, 0);      // Define which way is "up"
	free_matrix(world.camera.transform); // Free the default identity matrix
	world.camera.transform = view_transform(from, to, up);

	// Render the scene
	init_window(&world);
	render_scene(&world);
	mlx_loop(world.mlx.mlx_ptr);
	
	free_scene(&world);
	return (0);
}