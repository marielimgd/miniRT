/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:18:57 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:18:57 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "minirt.h"

// --- Window Functions ---
void		init_window(struct s_scene *scene);
int			close_window(struct s_scene *scene);
int			handle_keypress(int keycode, struct s_scene *scene);
void		validate_scene(struct s_scene *scene);
void		validate_filename(char *filename);
void		export_bmp(struct s_scene *world);
void		print_initial_object_selection(struct s_scene *scene);

// --- Camera Controls ---
void		update_camera_transform(t_camera *cam);
void		handle_camera_controls(int keycode, struct s_scene *scene,
				bool *needs_rerender);
void		handle_camera_rotation(int keycode, struct s_scene *scene,
				bool *needs_rerender);

// --- Light Controls ---
void		handle_light_controls(int keycode, struct s_scene *scene,
				bool *needs_rerender);
void		handle_light_transform(int keycode, struct s_scene *scene,
				bool *needs_rerender);

// --- Object Controls ---
void		print_object_info(t_object *obj);
void		resize_sphere(t_object *obj, int keycode, bool *needs_rerender);
void		resize_cylinder_diameter(t_object *obj, int keycode,
				bool *needs_rerender);
void		resize_cylinder_height(t_object *obj, int keycode,
				bool *needs_rerender);
void		cycle_object_selection(struct s_scene *scene,
				bool *needs_rerender);

// --- Object Transform ---
void		handle_object_transform_rotation(int keycode,
				struct s_scene *scene, bool *needs_rerender);
void		handle_object_controls(int keycode, struct s_scene *scene,
				bool *needs_rerender);

#endif