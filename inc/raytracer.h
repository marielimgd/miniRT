/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:36:30 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/03 20:56:52 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
#define RAYTRACER_H

# include "minirt.h"

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

// --- Rendering ---
void		render_scene(struct s_scene *scene);
void		my_mlx_pixel_put(struct s_mlx_data *data, int x, int y,
				struct s_color color);
t_vector	calculate_ray_direction(t_camera *camera, int x, int y);


// --- Intersections ---






// --- Safe_Malloc ---
void			*safe_malloc(size_t size, t_alloc_type u_type);
void			free_all(void);
t_allocation	*get_alloc();

#endif