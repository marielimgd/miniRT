/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/09 16:35:32 by mmariano         ###   ########.fr       */
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
	return (0);
} */

//----------------------------------------------TEST AREA----------------------------------------

/* static void	setup_scene(t_scene *scene)
{
	t_object	*sphere;
	t_matrix	*transform;

	sphere = create_sphere();

	transform = scaling(0.5, 1, 1);
	set_transform(sphere, transform);

	scene->objects = ft_lstnew(sphere);
} */


/*void	render_sphere_shadow(t_scene *scene)
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

	ray_origin = (t_vector){0, 0, -5, 1};
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
			if (find_hit(&xs))
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
} */


// Helper function to compare two vectors for equality
static bool	are_vectors_equal(t_vector v1, t_vector v2)
{
	if (!is_equal(v1.x, v2.x))
		return (false);
	if (!is_equal(v1.y, v2.y))
		return (false);
	if (!is_equal(v1.z, v2.z))
		return (false);
	if (!is_equal(v1.w, v2.w))
		return (false);
	return (true);
}

// Test: The normal on a sphere at a point on the x axis
static void	test_normal_on_x_axis(void)
{
	t_object	*s;
	t_vector	p;
	t_vector	n;
	t_vector	expected;

	s = create_sphere();
	p = create_point(1, 0, 0);
	n = normal_at(s, p);
	expected = create_vector(1, 0, 0);
	if (are_vectors_equal(n, expected))
		printf("PASS: Normal on x-axis is correct.\n");
	else
		printf("FAIL: Normal on x-axis is incorrect.\n");
	free_all(); // Clears memory for the next test
}

// Test: The normal on a sphere at a point on the y axis
static void	test_normal_on_y_axis(void)
{
	t_object	*s;
	t_vector	p;
	t_vector	n;
	t_vector	expected;

	s = create_sphere();
	p = create_point(0, 1, 0);
	n = normal_at(s, p);
	expected = create_vector(0, 1, 0);
	if (are_vectors_equal(n, expected))
		printf("PASS: Normal on y-axis is correct.\n");
	else
		printf("FAIL: Normal on y-axis is incorrect.\n");
	free_all();
}

// Test: The normal on a sphere at a point on the z axis
static void	test_normal_on_z_axis(void)
{
	t_object	*s;
	t_vector	p;
	t_vector	n;
	t_vector	expected;

	s = create_sphere();
	p = create_point(0, 0, 1);
	n = normal_at(s, p);
	expected = create_vector(0, 0, 1);
	if (are_vectors_equal(n, expected))
		printf("PASS: Normal on z-axis is correct.\n");
	else
		printf("FAIL: Normal on z-axis is incorrect.\n");
	free_all();
}

// Test: The normal on a sphere at a nonaxial point
static void	test_normal_nonaxial(void)
{
	t_object	*s;
	t_vector	p;
	t_vector	n;
	t_vector	expected;
	double		val;

	s = create_sphere();
	val = sqrt(3.0) / 3.0;
	p = create_point(val, val, val);
	n = normal_at(s, p);
	expected = create_vector(val, val, val);
	if (are_vectors_equal(n, expected))
		printf("PASS: Normal on a non-axial point is correct.\n");
	else
		printf("FAIL: Normal on a non-axial point is incorrect.\n");
	free_all();
}

// Test: The normal vector is normalized
static void	test_normal_is_normalized(void)
{
	t_object	*s;
	t_vector	p;
	t_vector	n;
	double		val;

	s = create_sphere();
	val = sqrt(3.0) / 3.0;
	p = create_point(val, val, val);
	n = normal_at(s, p);
	if (is_equal(get_magnitude(&n), 1.0))
		printf("PASS: The normal vector is normalized.\n");
	else
		printf("FAIL: The normal vector is not normalized.\n");
	free_all();
}

int	main(void)
{
	printf("--- Running Sphere Normal Tests ---\n");
	test_normal_on_x_axis();
	test_normal_on_y_axis();
	test_normal_on_z_axis();
	test_normal_nonaxial();
	test_normal_is_normalized();
	printf("--- All tests finished. ---\n");
	return (0);
}