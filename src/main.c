/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/10 14:17:39 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_scene(t_scene *scene)
{
	scene->ambient_light = -1.0;
	scene->has_ambient = false;
	scene->lights = NULL;
	scene->objects = NULL;
}

int	main(int argc, char **argv)
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
}

//----------------------------------------------TEST AREA----------------------------------------
