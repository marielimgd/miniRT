/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:36:30 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/16 16:58:21 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
#define RAYTRACER_H

# include "minirt.h"

t_vector	create_point(double x, double y, double z);
t_vector	create_vector(double x, double y, double z);

// --- Vector Math ---
double		get_magnitude(t_vector *vector);
void		normalization(t_vector *result, t_vector *u_vector);
void		negative_vector(t_vector *result, t_vector *vector);
double		dot_product(t_vector *a, t_vector *b);
void		dot_cross(t_vector *result, t_vector *a, t_vector *b);
int			is_equal(double a, double b);
void		add_tuples(t_vector *result, t_vector *vector, t_vector *point);
void		subtract_tuples(t_vector *result, t_vector *vector, t_vector *point);
void		scale_tuples_product(t_vector *result, t_vector *vector, double scale);
void		scale_tuples_divison(t_vector *result, t_vector *vector, double scale);
bool		are_vectors_equal(t_vector a, t_vector b);

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
t_matrix	*rotation_x(double radians);
t_matrix	*rotation_y(double radians);
t_matrix	*rotation_z(double radians);
t_matrix	*rotation_from_orientation(t_vector orientation); // Add this line
double		cofactor(t_matrix *m, int row, int col);
double		determinant(t_matrix *m);


//--- Color ---
t_color	    max_color(t_color c);
t_color	    scale_color(t_color c, float ratio);
t_color	    add_color(t_color a, t_color b);
t_color	    subtract_color(t_color a, t_color b);
t_color	    multiply_color(t_color a, t_color b);
t_color	    color_at(t_scene *world, t_ray ray);

// --- Scene ---
t_scene	    *create_world(void);
void	    create_default_world(t_scene *world); // ONLY FOR TESTING
t_color	    lighting(t_material m, t_light *light, t_comps *comps, bool in_shadow);
void	    reflect(t_vector *result,t_vector *in, t_vector *normal);

// --- Window ---
void	init_window(t_scene *scene);
int	    close_window(t_scene *scene);
int	    handle_mouse_scroll(int button, int x, int y, t_scene *scene);
int	    handle_keypress(int keycode, t_scene *scene);


// --- Rendering ---
void		render_scene(struct s_scene *scene);
void		my_mlx_pixel_put(struct s_mlx_data *data, int x, int y, struct s_color color);
void	    prepare_computations(t_comps *comps, t_intersection *i, t_ray *ray);


// --- Ray ---
t_vector	calculate_ray_direction(t_camera *camera, int x, int y);
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	ray_position(t_ray ray, double t);
t_ray		transform(t_ray ray, t_matrix *m);
void		set_transform(t_object *s, t_matrix *t);


// --- Camera ---
void		camera_init(t_camera *cam, int hsize, int vsize, double fov);
t_matrix	*view_transform(t_vector from, t_vector to, t_vector up);
t_matrix	*create_orientation_matrix(t_orientation_vectors *vecs);
void		calculate_orientation_vectors(t_orientation_vectors *vecs, t_vector from, t_vector to, t_vector up);
t_ray	    ray_for_pixel(t_camera *camera, int px, int py);


// --- Intersections ---
t_intersection		intersect_object(t_object *object, t_ray ray);
t_intersection		create_intersection(double t, t_object *obj);
t_intersection_list	create_intersections_list(int count, ...);
t_intersection		*find_hit(t_intersection_list *list);
t_color				shade_hit(t_scene *scene, t_comps *comps);
t_intersection_list	intersect_world(t_scene *scene, t_ray ray);

// --- Objects ----
t_object	        *create_sphere(void);
t_intersection_list	intersect_sphere(t_object *sphere, t_ray ray);
t_vector	        normal_at(t_object *sphere, t_vector world_point);
t_vector	        normal_at_sphere(t_object *sphere, t_vector world_point);
t_object	        *create_plane(void);
t_intersection_list	intersect_plane(t_object *plane, t_ray ray);
t_vector	        normal_at_plane(t_object *plane, t_vector world_point);

// --- Safe_Malloc ---
void			*safe_malloc(size_t size, t_alloc_type u_type);
void			free_all(void);
t_allocation	**get_alloc_head(void);
void			free_matrix(t_matrix *m);
void			free_object(void *obj_ptr);
void			free_light(void *light_ptr);
void			free_scene(t_scene *scene);


// --- Error ---
void	print_error(char *s);

#endif