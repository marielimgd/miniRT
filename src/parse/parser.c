/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:09:57 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/23 18:56:17 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_scene_utils(char ***tokens, char **line, \
	int line_number, t_scene *scene);

static void	parse_elements(char **tokens, t_scene *scene, int line_number)
{
	if (ft_strcmp(tokens[0], "A") == 0)
		parse_ambient_light(tokens, scene, line_number);
	else if (ft_strcmp(tokens[0], "C") == 0)
		parse_camera(tokens, scene, line_number);
	else if (ft_strcmp(tokens[0], "L") == 0)
		parse_light(tokens, scene, line_number);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		parse_plane(tokens, scene, line_number);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		parse_sphere(tokens, scene, line_number);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		parse_cylinder(tokens, scene, line_number);
	else
	{
		ft_putstr_fd("Unknown element type in scene file: ", 2);
		ft_putendl_fd(tokens[0], 2);
	}
}

void	parse_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**tokens;
	int		line_number;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		parse_error(0, "Failed to open the scene file");
	line_number = 0;
	line = get_next_line(fd);
	while (line != NULL && line_number++ >= 0)
	{
		if (line[0] == '\0' || line[0] == '#')
		{
			free(line);
			continue ;
		}
		parse_scene_utils(&tokens, &line, line_number, scene);
		free_tokens(tokens);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

static void	parse_scene_utils(char ***tokens, char **line, \
	int line_number, t_scene *scene)
{
	*tokens = ft_split(*line, ' ');
	if (!(*tokens))
		parse_error(line_number, "Memory allocation failed during parsing");
	parse_elements(*tokens, scene, line_number);
}
