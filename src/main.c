/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/11 19:31:06 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static void	init_scene(t_scene *scene)
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
} */

//----------------------------------------------TEST AREA----------------------------------------

static void	print_test_result(const char *test_name, bool success)
{
	if (success)
		printf("✅  PASS: %s\n", test_name);
	else
		printf("❌  FAIL: %s\n", test_name);
}

// --- Test Scenarios ---

void	test_normal_on_x_axis(void)
{
	t_object	*s = create_sphere();
	t_vector	p = create_point(1, 0, 0);
	t_vector	n = normal_at(s, p);
	t_vector	expected = create_vector(1, 0, 0);
	
	print_test_result("The normal on a sphere at a point on the x axis", are_vectors_equal(n, expected));
	free(s->transform);
	free(s);
}

void	test_normal_on_y_axis(void)
{
	t_object	*s = create_sphere();
	t_vector	p = create_point(0, 1, 0);
	t_vector	n = normal_at(s, p);
	t_vector	expected = create_vector(0, 1, 0);

	print_test_result("The normal on a sphere at a point on the y axis", are_vectors_equal(n, expected));
	free(s->transform);
	free(s);
}

void	test_normal_on_z_axis(void)
{
	t_object	*s = create_sphere();
	t_vector	p = create_point(0, 0, 1);
	t_vector	n = normal_at(s, p);
	t_vector	expected = create_vector(0, 0, 1);

	print_test_result("The normal on a sphere at a point on the z axis", are_vectors_equal(n, expected));
	free(s->transform);
	free(s);
}

void	test_normal_nonaxial(void)
{
	t_object	*s = create_sphere();
	double		val = sqrt(3.0) / 3.0;
	t_vector	p = create_point(val, val, val);
	t_vector	n = normal_at(s, p);
	t_vector	expected = create_vector(val, val, val);

	print_test_result("The normal on a sphere at a nonaxial point", are_vectors_equal(n, expected));
	free(s->transform);
	free(s);
}

void	test_normal_is_normalized(void)
{
	t_object	*s = create_sphere();
	double		val = sqrt(3.0) / 3.0;
	t_vector	p = create_point(val, val, val);
	t_vector	n = normal_at(s, p);
	t_vector	*normalized_n = normalization(&n);
	
	print_test_result("The normal is a normalized vector", are_vectors_equal(n, *normalized_n));
	free(s->transform);
	free(s);
	free(normalized_n);
}

// --- Test Runner ---

int	main(void)
{
	printf("--- Running Sphere Normal Tests ---\n");
	test_normal_on_x_axis();
	test_normal_on_y_axis();
	test_normal_on_z_axis();
	test_normal_nonaxial();
	test_normal_is_normalized();
	printf("---------------------------------\n");
	// free_all();
	return (0);
}