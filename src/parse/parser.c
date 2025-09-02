/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:09:57 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/02 16:42:34 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static void parse_elements(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0) //ambient light
		parse_ambient_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "C") == 0) //camera
		parse_camera(tokens, scene);
	else if (ft_strcmp(tokens[0], "L") == 0) //light
		parse_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0) // Plane
		parse_plane(tokens, scene);
	else if (ft_strcmp(tokens[0], "sp") == 0) // Sphere
		parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "cy") == 0) //cylinder
		parse_cylinder(tokens, scene);
	else
		printf("Unknown element type in scene file: %s\n", tokens[0]);

}

void parse_scene(char *file, t_scene *scene)
{
	int fd;
	char *line;
	char **tokens;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		parse_error("Failed to open the scene file\n");

	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '\0' || line[0] == '#')
		{
			free(line);
			continue;
		}
		tokens = ft_split(line, ' ');
		if (!tokens)
			parse_error("Memory allocation failed during parsing\n");
		parse_elements(tokens, scene);
		free_tokens(tokens);
		free(line);
	}
	close(fd);
}
	