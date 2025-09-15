#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

// --- Element parsers ---
void		parse_scene(char *file, t_scene *scene);
void		parse_ambient_light(char **tokens, t_scene *scene,int line_number);
void		parse_camera(char **tokens, t_scene *scene, int line_number);
void		parse_light(char **tokens, t_scene *scene, int line_number);
void		parse_sphere(char **tokens, t_scene *scene, int line_number);
void		parse_plane(char **tokens, t_scene *scene, int line_number);
void		parse_cylinder(char **tokens, t_scene *scene, int line_number);

// --- Utility functions ---
void	parse_error(int line_number, char *message);
int			count_tokens(char **tokens);
void		free_tokens(char **tokens);
t_vector	string_to_vector(char *str, double w_value);
t_color		parse_colors(char *str);



#endif