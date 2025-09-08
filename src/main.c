/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/08 16:14:59 by mmariano         ###   ########.fr       */
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
void	print_tuple(t_vector t, char *name)
{
	printf("%s: (x:%.1f, y:%.1f, z:%.1f, w:%.1f)\n",
		name, t.x, t.y, t.z, t.w);
}

void	print_intersections(t_intersection_list xs, char *name)
{
	printf("%s: count = %d", name, xs.count);
	if (xs.count > 0)
		printf(", t[0] = %.1f, t[1] = %.1f\n", xs.intersections[0].t, xs.intersections[1].t);
	else
		printf("\n");
}

// Helper to print a 4x4 matrix
void	print_matrix(t_matrix *m, char *name)
{
	int	i;
	int	j;

	printf("--- Matrix: %s ---\n", name);
	if (!m)
	{
		printf(" (NULL)\n");
		return ;
	}
	i = 0;
	while (i < m->row)
	{
		j = 0;
		printf("|");
		while (j < m->collum)
		{
			printf(" %.2f ", m->matrix[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("---------------------\n");
}

// Helper to compare two matrices
void	compare_matrices(t_matrix *a, t_matrix *b, char *name)
{
	int	i;
	int	j;
	int	equal;

	equal = 1;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (!is_equal(a->matrix[i][j], b->matrix[i][j]))
				equal = 0;
			j++;
		}
		i++;
	}
	printf("%s: %s\n", name, (equal ? "PASS" : "FAIL"));
}

int	main(void)
{
	t_ray				r;
	t_ray				r2;
	t_matrix			*m;
	t_object			*s;
	t_intersection_list	xs;
	t_matrix			*t;
	t_matrix			*ident;

	// --- Ray Transformation Tests ---
	printf("--- SCENARIO: Translating a ray ---\n");
	r = create_ray(create_point(1, 2, 3), create_vector(0, 1, 0));
	m = translation(3, 4, 5);
	r2 = transform(r, m);
	print_tuple(r2.origin, "r2.origin");    // Expected: (4, 6, 8)
	print_tuple(r2.direction, "r2.direction"); // Expected: (0, 1, 0)
	printf("\n");

	printf("--- SCENARIO: Scaling a ray ---\n");
	r = create_ray(create_point(1, 2, 3), create_vector(0, 1, 0));
	m = scaling(2, 3, 4);
	r2 = transform(r, m);
	print_tuple(r2.origin, "r2.origin");    // Expected: (2, 6, 12)
	print_tuple(r2.direction, "r2.direction"); // Expected: (0, 3, 0)
	printf("\n");

	// --- Sphere Transformation Tests ---
	printf("--- SCENARIO: A sphere's default transformation ---\n");
	s = create_sphere();
	ident = identity_matrix();
	compare_matrices(s->transform, ident, "Default transform is identity");
	printf("\n");

	printf("--- SCENARIO: Changing a sphere's transformation ---\n");
	t = translation(2, 3, 4);
	set_transform(s, t);
	compare_matrices(s->transform, t, "Transform has been set");
	printf("\n");

	// --- Intersection with Transformed Spheres ---
	printf("--- SCENARIO: Intersecting a scaled sphere ---\n");
	r = create_ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	set_transform(s, scaling(2, 2, 2));
	xs = intersect_sphere(s, r);
	print_intersections(xs, "xs"); // Expected: count=2, t=3.0, t=7.0
	printf("\n");

	printf("--- SCENARIO: Intersecting a translated sphere ---\n");
	r = create_ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	set_transform(s, translation(5, 0, 0));
	xs = intersect_sphere(s, r);
	print_intersections(xs, "xs"); // Expected: count=0
	printf("\n");
	
	free_all();
	return (0);
}


