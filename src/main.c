/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/11 20:03:01 by marieli          ###   ########.fr       */
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


// src/test/test_phong_lighting.c

#include "minirt.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// --- Test Helper Functions ---

static bool	are_colors_equal(t_color c1, t_color c2)
{
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

static void	print_test_result(const char *test_name, bool success)
{
	if (success)
		printf("✅  PASS: %s\n", test_name);
	else
		printf("❌  FAIL: %s\n", test_name);
}

// --- Test Scenarios ---

// Setup shared by all tests
static void	setup_lighting_test(t_material *m, t_light *light, t_lighting_data *d)
{
	m->color = (t_color){255, 255, 255};
	m->ambient = 0.1;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200.0;
	light->brightness = 1.0;
	light->color = (t_color){255, 255, 255};
	d->point = create_point(0, 0, 0);
}

void	test_eye_between_light_and_surface(void)
{
	t_material m;
	t_light light;
	t_lighting_data d;
	
	setup_lighting_test(&m, &light, &d);
	d.eyev = create_vector(0, 0, -1);
	d.normalv = create_vector(0, 0, -1);
	light.origin = create_point(0, 0, -10);

	t_color result = lighting(m, &light, d);
	// Expected: ambient(25) + diffuse(229) + specular(229) = 483 -> clamped to 255
	t_color expected = (t_color){255, 255, 255};
	print_test_result("Lighting with eye between light and surface", are_colors_equal(result, expected));
}

void	test_eye_offset_45_degrees(void)
{
	t_material m;
	t_light light;
	t_lighting_data d;

	setup_lighting_test(&m, &light, &d);
	d.eyev = create_vector(0, sqrt(2.0)/2.0, -sqrt(2.0)/2.0);
	d.normalv = create_vector(0, 0, -1);
	light.origin = create_point(0, 0, -10);

	t_color result = lighting(m, &light, d);
	// Expected: ambient(25) + diffuse(229) = 254. Specular is 0.
	t_color expected = (t_color){254, 254, 254};
	print_test_result("Lighting with eye offset 45°", are_colors_equal(result, expected));
}

void	test_light_offset_45_degrees(void)
{
	t_material m;
	t_light light;
	t_lighting_data d;

	setup_lighting_test(&m, &light, &d);
	d.eyev = create_vector(0, 0, -1);
	d.normalv = create_vector(0, 0, -1);
	light.origin = create_point(0, 10, -10);

	t_color result = lighting(m, &light, d);
	// Expected: ambient(25) + diffuse(162) = 187. Specular is 0.
	t_color expected = (t_color){187, 187, 187};
	print_test_result("Lighting with light offset 45°", are_colors_equal(result, expected));
}

void	test_eye_in_reflection_path(void)
{
	t_material m;
	t_light light;
	t_lighting_data d;
	
	setup_lighting_test(&m, &light, &d);
	d.eyev = create_vector(0, -sqrt(2.0)/2.0, -sqrt(2.0)/2.0);
	d.normalv = create_vector(0, 0, -1);
	light.origin = create_point(0, 10, -10);

	t_color result = lighting(m, &light, d);
	// Expected: ambient(25) + diffuse(162) + specular(229) = 416 -> clamped to 255
	t_color expected = (t_color){255, 255, 255};
	print_test_result("Lighting with eye in reflection path", are_colors_equal(result, expected));
}

void	test_light_behind_surface(void)
{
	t_material m;
	t_light light;
	t_lighting_data d;
	
	setup_lighting_test(&m, &light, &d);
	d.eyev = create_vector(0, 0, -1);
	d.normalv = create_vector(0, 0, -1);
	light.origin = create_point(0, 0, 10);

	t_color result = lighting(m, &light, d);
	// Expected: ambient(25). Diffuse and specular are 0.
	t_color expected = (t_color){25, 25, 25};
	print_test_result("Lighting with light behind surface", are_colors_equal(result, expected));
}


// --- Test Runner ---

int	main(void)
{
	printf("--- Running Full Phong Lighting Tests ---\n");
	test_eye_between_light_and_surface();
	test_eye_offset_45_degrees();
	test_light_offset_45_degrees();
	test_eye_in_reflection_path();
	test_light_behind_surface();
	printf("---------------------------------------\n");
	free_all();
	return (0);
}