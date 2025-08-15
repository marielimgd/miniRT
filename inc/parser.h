/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:54:36 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/14 20:31:15 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"


t_color	parse_colors(char *str);
void 	parse_camera(char**tokens, t_scene *scene);
void 	parse_ambient_light(char**tokens, t_scene *scene);
void 	parse_light(char**tokens, t_scene *scene);
void 	parse_sphere(char**tokens, t_scene *scene);
void 	parse_cylinder(char**tokens, t_scene *scene);
void 	parse_error(char *message);
void 	free_tokens(char **tokens);
int 	count_tokens(char **tokens);
