#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "minirt.h"

// --- Vector Math ---
t_vector	add_vectors(t_vector a, t_vector b);
t_vector	subtract_vectors(t_vector a, t_vector b);
t_vector	multiply_scalar(t_vector vector, double scalar);
t_vector	divide_scalar(t_vector vector, double scalar);
double		vector_magnitude(t_vector vector);
t_vector	vector_normalize(t_vector v);
double		vector_dot_product(t_vector a, t_vector b);
t_vector	vector_cross_product(t_vector a, t_vector b);

// --- Rendering ---
void		render_scene(struct s_scene *scene);
void		my_mlx_pixel_put(struct s_mlx_data *data, int x, int y,
				struct s_color color);

// --- Intersections ---

#endif