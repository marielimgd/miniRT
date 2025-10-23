/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:34:20 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:34:20 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_scene(t_scene *scene)
{
	if (!scene->has_camera)
		parse_error(0, "Scene must have a camera 'C'");
	if (!scene->has_ambient)
		parse_error(0, "Scene must have ambient light 'A'");
	if (!scene->lights)
		parse_error(0, "Scene must have at least one light 'L'");
}

static void	print_controls(void)
{
	printf("\nControls:\n");
	printf("  O: Cycle selected object\n");
	printf("  , (comma): Decrease diameter\n");
	printf("  . (dot): Increase diameter\n");
	printf("  H: Increase cylinder height\n");
	printf("  G: Decrease cylinder height\n\n");
}

static void	print_selected_object(t_object *obj, double pos[3])
{
	printf("\n=== Initial Object Selection ===\n");
	if (obj->type == SPHERE)
		printf("Selected: SPHERE | Diameter: %.2f | Position: \
(%.1f, %.1f, %.1f)\n", \
obj->prop.sphere.radius * 2.0, pos[0], pos[1], pos[2]);
	else if (obj->type == PLANE)
		printf("Selected: PLANE | Position: (%.1f, %.1f, %.1f)\n",
			pos[0], pos[1], pos[2]);
	else if (obj->type == CYLINDER)
		printf("Selected: CYLINDER | Diameter: %.2f | Height: %.2f"
			" | Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.cylinder.diameter, obj->prop.cylinder.height,
			pos[0], pos[1], pos[2]);
}

void	print_initial_object_selection(t_scene *scene)
{
	t_object	*obj;
	double		pos[3];

	if (!scene->selected_object || !scene->selected_object->data)
	{
		printf("\nNo objects in scene to select.\n");
		return ;
	}
	obj = (t_object *)scene->selected_object->data;
	pos[0] = obj->transform->matrix[0][3];
	pos[1] = obj->transform->matrix[1][3];
	pos[2] = obj->transform->matrix[2][3];
	print_selected_object(obj, pos);
	print_controls();
}
