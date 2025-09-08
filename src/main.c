/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/08 18:20:28 by mmariano         ###   ########.fr       */
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
	return (0);
} */

//----------------------------------------------TEST AREA----------------------------------------

static void	setup_scene(t_scene *scene)
{
	t_object	*sphere;
	t_matrix	*transform;

	// Create a sphere and add it to the scene's object list.
	sphere = create_sphere();

	// Example transform: shrink the sphere and move it a little.
	// You can comment this out to render the default unit sphere.
	transform = scaling(0.5, 1, 1);
	set_transform(sphere, transform);

	scene->objects = ft_lstnew(sphere);
}

#include "minirt.h"

// Your init_scene and setup_scene functions...

void	render_sphere_shadow(t_scene *scene)
{
	int			x;
	int			y;
	t_vector	world_coords;
	t_ray		r;
	t_intersection_list	xs;
	t_vector	wall_position;
	t_vector	*dir_unnormalized;
	t_vector	*dir_normalized;
	t_vector	ray_origin;

	ray_origin = (t_vector){0, 0, -5, 1}; // Direct initialization
	double wall_z = 10.0;
	double wall_size = 7.0;
	double pixel_size = wall_size / WIDTH;
	double half_wall = wall_size / 2.0;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			world_coords.x = -half_wall + pixel_size * x;
			world_coords.y = half_wall - pixel_size * y;
			wall_position = (t_vector){world_coords.x, world_coords.y, wall_z, 1};
			dir_unnormalized = subtract_tuples(&wall_position, &ray_origin);
			dir_normalized = normalization(dir_unnormalized);
			r = create_ray(ray_origin, *dir_normalized);
			
			free(dir_unnormalized);
			free(dir_normalized);
			
			xs = intersect_sphere(scene->objects->data, r);
			if (find_hit(xs))
				my_mlx_pixel_put(&scene->mlx, x, y, (t_color){255, 0, 0});
			else
				my_mlx_pixel_put(&scene->mlx, x, y, (t_color){25, 25, 25});
		}
	}
}

int	main(void)
{
	t_scene	scene;

	init_scene(&scene);
	init_window(&scene);
	setup_scene(&scene);
	render_sphere_shadow(&scene);
	mlx_put_image_to_window(scene.mlx.mlx_ptr, scene.mlx.win_ptr,
		scene.mlx.img_ptr, 0, 0);
	mlx_loop(scene.mlx.mlx_ptr);
	free_all();
	return (0);
}
