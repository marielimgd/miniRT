/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:09:57 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/14 20:42:23 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"
#include "parser.h"


static void parse_elements(char **tokens, char *line, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0) // Ambient light
		parse_ambient_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "C") == 0) // Camera
		parse_camera(tokens, scene);
	else if (ft_strcmp(tokens[0], "L") == 0) // Light
		parse_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "SP") == 0) // Sphere
		parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "CY") == 0) // Cylinder
		parse_cylinder(tokens, scene);
	else
		parse_error("Unknown element type in scene file\n");

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
		parse_elements(tokens, line, scene);
		free_tokens(tokens);
		free(line);
	}
	close(fd);
}
	
