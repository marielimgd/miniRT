/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:18:20 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:18:20 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdarg.h>

/* Forward declarations to avoid circular includes with minirt.h */
typedef struct s_scene t_scene;
typedef struct s_object t_object;
typedef struct s_vector t_vector;
typedef struct s_matrix t_matrix;
typedef struct s_color t_color;

// --- Element parsers ---
void		parse_scene(char *file, t_scene *scene);
void		parse_ambient_light(char **tokens, t_scene *scene, int line_number);
void		parse_camera(char **tokens, t_scene *scene, int line_number);
void		parse_light(char **tokens, t_scene *scene, int line_number);
void		parse_sphere(char **tokens, t_scene *scene, int line_number);
void		parse_plane(char **tokens, t_scene *scene, int line_number);
void		parse_cylinder(char **tokens, t_scene *scene, int line_number);

// --- Object helper functions ---
void		set_sphere_transform(t_object *sphere, t_vector position,
				double diameter);
void		set_sphere_material(t_object *sphere, char *color_str);
void		set_plane_transform(t_object *plane, t_vector position,
				t_vector normal);
void		set_plane_material(t_object *plane, char *color_str);
void		set_cylinder_material(t_object *cylinder, char *color_str);
void		init_cylinder_properties(t_object *cylinder, char **tokens,
				int line_number);
void		set_cylinder_transform(t_object *cylinder, t_vector origin, \
				t_vector orientation, double diameter, double height);
t_matrix	*set_cylinder_transform_utils(t_matrix *rotation_m, \
				t_vector *orientation);

// --- Utility functions ---
void		parse_error(int line_number, char *message);
int			count_tokens(char **tokens);
void		free_tokens(char **tokens);
t_vector	string_to_vector(char *str, double w_value);
t_color		parse_colors(char *str);

#endif