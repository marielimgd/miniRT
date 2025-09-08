/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:36:30 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/08 18:20:23 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
#define RAYTRACER_H

# include "minirt.h"

t_vector	create_point(double x, double y, double z);
t_vector	create_vector(double x, double y, double z);

// --- Vector Math ---
double		get_magnitude(t_vector *vector);
t_vector	*normalization(t_vector *u_vector);
t_vector	*negative_vector(t_vector *vector);
double		dot_product(t_vector *a, t_vector *b);
t_vector	*dot_cross(t_vector *a, t_vector *b);
int			is_equal(double a, double b);
t_vector	*add_tuples(t_vector *vector, t_vector *point);
t_vector	*subtract_tuples(t_vector *vector, t_vector *point);
t_vector	*scale_tuples_product(t_vector *vector, double scale);
t_vector	*scale_tuples_divison(t_vector *vector, double scale);

// --- Matrix ----
t_matrix	*create_matrix(double collum, double row);
t_matrix	*matrix_product(t_matrix *a, t_matrix *b);
t_matrix	*tuple_to_matrix(t_vector *tuple);
t_matrix	*identity_matrix(void);
t_matrix	*transpose_matrix(t_matrix *a);
t_matrix	*inverse_matrix(t_matrix *a);
t_matrix	*translation(double x, double y, double z);
t_matrix	*scaling(double x, double y, double z);
t_vector	multiply_matrix_by_tuple(t_matrix *m, t_vector t);
void		free_matrix(t_matrix *m);
t_matrix	*rotation_x(double radians);
t_matrix	*rotation_y(double radians);
t_matrix	*rotation_z(double radians);


//DELETAR DEPOIS
double			cofactor(t_matrix *m, int row, int col);
double			determinant(t_matrix *m);

// --- Rendering ---
void		render_scene(struct s_scene *scene);
void		my_mlx_pixel_put(struct s_mlx_data *data, int x, int y,
				struct s_color color);

// --- Ray ---
t_vector	calculate_ray_direction(t_camera *camera, int x, int y);
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	ray_position(t_ray ray, double t);
t_ray		transform(t_ray ray, t_matrix *m);
void		set_transform(t_object *s, t_matrix *t);


// --- Intersections ---
t_intersection		intersect_object(t_object *object, t_ray ray);
t_intersection		create_intersection(double t, t_object *obj);
t_intersection_list	create_intersections_list(int count, ...);
t_intersection		*find_hit(t_intersection_list list);



// --- Objects ----
t_object	*create_sphere(void);
t_intersection_list	intersect_sphere(t_object *sphere, t_ray ray);

// --- Safe_Malloc ---
void			*safe_malloc(size_t size, t_alloc_type u_type);
void			free_all(void);
t_allocation	*get_alloc();


// --- Error ---
void	print_error(char *s);

#endif