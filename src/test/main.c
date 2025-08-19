/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:27:39 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/19 16:22:58 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*--------------------------------Main para testar o parser----------------------------------*/


#include "parser.h"
#include "scene.h"

static void	init_scene(t_scene *scene)
{
	scene->ambient_light = -1.0;
	scene->has_ambient = 0;
	scene->lights = NULL;
	scene->objects = NULL;
}

static void print_scene(t_scene *scene)
{
	printf("\033[0;31m------Scene Data Test------\n\033[0m");
	if (scene->has_ambient)
	{
		printf("Camera parameters:\n");
		printf("Camera Orientation: (%.2f, %.2f, %.2f)\n", scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z);
		printf("Camera Origin: (%.2f, %.2f, %.2f)\n", scene->camera.origin.x, scene->camera.origin.y, scene->camera.origin.z);
		printf("Camera FOV: %d degrees\n", scene->camera.fov);
		printf("\n");
		printf("Ambient Light Parameters:\n");
		printf("Ambient Light: %.2f\n", scene->ambient_light);
		printf("Ambient Color: R: %d, G: %d, B: %d\n", scene->ambient_color.r, scene->ambient_color.g, scene->ambient_color.b);
		printf("Number of Lights: %d\n", ft_lstsize(scene->lights));
		printf("\n");

//count objects by type
	int cylinders = 0, planes = 0, spheres = 0;
	t_list *obj_node = scene->objects;
	while (obj_node)
	{
		t_object *obj = (t_object *)obj_node->data;
		if (obj->type == CYLINDER)
			cylinders++;
		else if (obj->type == PLANE)
			planes++;
		else if (obj->type == SPHERE)
			spheres++;
		obj_node = obj_node->next;
	}
	printf("Scene has %d cylinder(s), %d plane(s), %d sphere(s).\n", cylinders, planes, spheres);

//object params
	obj_node = scene->objects;
	int obj_index = 1;
	while (obj_node)
	{
		t_object *obj = (t_object *)obj_node->data;
		printf("Object %d:\n", obj_index);
		if (obj->type == CYLINDER)
			printf("  Type: Cylinder\n");
		else if (obj->type == PLANE)
			printf("  Type: Plane\n");
		else if (obj->type == SPHERE)
			printf("  Type: Sphere\n");
		else
			printf("  Type: Unknown (%d)\n", obj->type);
		printf("  Origin: (%.2f, %.2f, %.2f)\n", obj->origin.x, obj->origin.y, obj->origin.z);
		printf("  Color: R: %d, G: %d, B: %d\n\n", obj->color.r, obj->color.g, obj->color.b);
		obj_node = obj_node->next;
		obj_index++;
	}
		printf("Number of Objects: %d\n", ft_lstsize(scene->objects));
	}
	else
		printf("No ambient light set.\n");
	printf("\033[0;31m----------------------------\n\033[0m");
}

int main(int argc, char **argv)
{

	t_scene scene;
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene_file.rt>\n", 2);
		return (1);
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		ft_putstr_fd("Error: Could not open scene file.\n", 2);
		return (1);
	}
	char buf[1];
	size_t bytes_read = fread(buf, 1, 1, file);
	if (bytes_read == 0)
	{
		ft_putstr_fd("Error: Scene file is empty.\n", 2);
		fclose(file);
		return (1);
	}
	fclose(file);
	init_scene(&scene);
	printf("\033[0;36m------Scene Initialization------\033[0m\n");
	printf("Parsing scene file: %s\n", argv[1]);
	parse_scene(argv[1], &scene);
	print_scene(&scene);
    ft_lstclear(&scene.lights, free);
    ft_lstclear(&scene.objects, free);
	return (0);
}
