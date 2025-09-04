/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/04 19:00:15 by mmariano         ###   ########.fr       */
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
	return (0);
} */

//----------------------------------------------TEST AREA----------------------------------------

// Helper to print the create_intersection list
void	print_intersection_list(t_intersect_list list, char *name)
{
	printf("%s: count = %d\n", name, list.count);
	for (int i = 0; i < list.count; i++)
	{
		printf("  [%d] t = %.1f, object_id = %p\n", i,
			list.intersections[i].t, list.intersections[i].object);
	}
}

int	main(void)
{
	t_object			*s;
	t_intersection		i1;
	t_intersection		i2;
	t_intersect_list	xs;
	t_ray				r;

	// Scenario 1: An create_intersection encapsulates t and object
	printf("--- SCENARIO 1: Encapsulating t and object ---\n");
	s = create_sphere();
	i1 = create_intersection(3.5, s);
	printf("i1.t = %.1f (Expected: 3.5)\n", i1.t);
	printf("i1.object = %p (s = %p)\n", i1.object, s);
	printf("\n");

	// Scenario 2: Aggregating create_intersections
	printf("--- SCENARIO 2: Aggregating create_intersections ---\n");
	i1 = create_intersection(1, s);
	i2 = create_intersection(2, s);
	xs = create_intersections_list(2, i1, i2);
	print_intersection_list(xs, "xs");
	printf("\n");

	// Scenario 3: Intersect sets the object on the create_intersection
	printf("--- SCENARIO 3: Intersect sets the object ---\n");
	r = create_ray(create_vector(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
	xs = intersect_sphere(s, r);
	print_intersection_list(xs, "xs");
	printf("\n");

	// free_all();
	return (0);
}