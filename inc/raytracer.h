#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "minirt.h"

// --- Vector Math ---


// --- Rendering ---
void		render_scene(struct s_scene *scene);
void		my_mlx_pixel_put(struct s_mlx_data *data, int x, int y,
				struct s_color color);
t_vector	calculate_ray_direction(t_camera *camera, int x, int y);


// --- Intersections ---

#endif