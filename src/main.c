/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/13 19:42:07 by marieli          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_scene	*world;

	if (argc != 2)
		parse_error("Usage: ./miniRT <scene.rt>");

	// Create and initialize the world
	world = create_world();
	
	// Parse the scene file to populate the world with objects,
	// lights, and the camera setup.
	parse_scene(argv[1], world);

	// Initialize the window
	init_window(world);
	
	// Render the fully parsed scene
	render_scene(world);
	mlx_loop(world->mlx.mlx_ptr);

	// Use your master cleanup function
	free_all();

	return (0);
}