/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:55:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 14:48:29 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_camera_transform(t_camera *cam)
{
	t_vector	to;

	if (cam->transform)
		free_matrix(cam->transform);
	normalization(&cam->orientation, &cam->orientation);
	add_tuples(&to, &cam->from, &cam->orientation);
	cam->transform = view_transform(cam->from, to, cam->up);
}

static void	handle_light_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_light	*light;

	if (keycode == KEY_L && scene->lights)
	{
		scene->selected_light = scene->selected_light->next;
		if (scene->selected_light == NULL)
			scene->selected_light = scene->lights;
	}
	if (scene->selected_light == NULL)
		return ;
	light = (t_light *)scene->selected_light->data;
	if (keycode == PLUS_KEY)
	{
		light->brightness += 0.1;
		if (light->brightness > 1.0)
			light->brightness = 1.0;
		*needs_rerender = true;
	}
	else if (keycode == MINUS_KEY)
	{
		light->brightness -= 0.1;
		if (light->brightness < 0.0)
			light->brightness = 0.0;
		*needs_rerender = true;
	}
}

static void	print_object_info(t_object *obj)
{
	double	pos_x;
	double	pos_y;
	double	pos_z;

	/* Extract position from transform matrix (translation components) */
	pos_x = obj->transform->matrix[0][3];
	pos_y = obj->transform->matrix[1][3];
	pos_z = obj->transform->matrix[2][3];
	
	if (obj->type == SPHERE)
		printf("Selected: SPHERE | Diameter: %.2f | Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.sphere.radius * 2.0, pos_x, pos_y, pos_z);
	else if (obj->type == PLANE)
		printf("Selected: PLANE | Position: (%.1f, %.1f, %.1f)\n",
			pos_x, pos_y, pos_z);
	else if (obj->type == CYLINDER)
		printf("Selected: CYLINDER | Diameter: %.2f | Height: %.2f | Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.cylinder.diameter, obj->prop.cylinder.height,
			pos_x, pos_y, pos_z);
}

static void	handle_object_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_object	*obj;
	t_matrix	*translation_m;
	t_matrix	*scaling_m;

	if (!scene->selected_object || !scene->selected_object->data)
		return;
	obj = (t_object *)scene->selected_object->data;
	/* Cycle selected object */
	if (keycode == KEY_O && scene->objects)
	{
		scene->selected_object = scene->selected_object->next;
		if (scene->selected_object == NULL)
			scene->selected_object = scene->objects;
		obj = (t_object *)scene->selected_object->data;
		printf("\n=== Object Selection Changed ===\n");
		print_object_info(obj);
		*needs_rerender = true;
		return;
	}
	/* Resize controls: comma/dot adjust diameter for spheres/cylinders, h/g adjust height for cylinders */
	if (obj->type == SPHERE)
	{
		double pos_x = obj->transform->matrix[0][3];
		double pos_y = obj->transform->matrix[1][3];
		double pos_z = obj->transform->matrix[2][3];
		
		if (keycode == KEY_COMMA) /* decrease diameter */
		{
			obj->prop.sphere.radius -= 0.1;
			if (obj->prop.sphere.radius < 0.01)
				obj->prop.sphere.radius = 0.01;
			translation_m = translation(pos_x, pos_y, pos_z);
			scaling_m = scaling(obj->prop.sphere.radius, obj->prop.sphere.radius, obj->prop.sphere.radius);
			set_transform(obj, matrix_product(translation_m, scaling_m));
			free_matrix(translation_m);
			free_matrix(scaling_m);
			printf("\n=== Sphere Resized ===\n");
			print_object_info(obj);
			*needs_rerender = true;
			return;
		}
		else if (keycode == KEY_DOT) /* increase diameter */
		{
			obj->prop.sphere.radius += 0.1;
			translation_m = translation(pos_x, pos_y, pos_z);
			scaling_m = scaling(obj->prop.sphere.radius, obj->prop.sphere.radius, obj->prop.sphere.radius);
			set_transform(obj, matrix_product(translation_m, scaling_m));
			free_matrix(translation_m);
			free_matrix(scaling_m);
			printf("\n=== Sphere Resized ===\n");
			print_object_info(obj);
			*needs_rerender = true;
			return;
		}
	}
	else if (obj->type == CYLINDER)
	{
		double pos_x = obj->transform->matrix[0][3];
		double pos_y = obj->transform->matrix[1][3];
		double pos_z = obj->transform->matrix[2][3];
		
		if (keycode == KEY_COMMA) /* decrease diameter */
		{
			obj->prop.cylinder.diameter -= 0.1;
			if (obj->prop.cylinder.diameter < 0.01)
				obj->prop.cylinder.diameter = 0.01;
			translation_m = translation(pos_x, pos_y, pos_z);
			scaling_m = scaling(obj->prop.cylinder.diameter / 2.0, 1.0, obj->prop.cylinder.diameter / 2.0);
			set_transform(obj, matrix_product(translation_m, scaling_m));
			free_matrix(translation_m);
			free_matrix(scaling_m);
			printf("\n=== Cylinder Diameter Changed ===\n");
			print_object_info(obj);
			*needs_rerender = true;
			return;
		}
		else if (keycode == KEY_DOT) /* increase diameter */
		{
			obj->prop.cylinder.diameter += 0.1;
			translation_m = translation(pos_x, pos_y, pos_z);
			scaling_m = scaling(obj->prop.cylinder.diameter / 2.0, 1.0, obj->prop.cylinder.diameter / 2.0);
			set_transform(obj, matrix_product(translation_m, scaling_m));
			free_matrix(translation_m);
			free_matrix(scaling_m);
			printf("\n=== Cylinder Diameter Changed ===\n");
			print_object_info(obj);
			*needs_rerender = true;
			return;
		}
		else if (keycode == KEY_H) /* increase height */
		{
			obj->prop.cylinder.height += 0.1;
			printf("\n=== Cylinder Height Changed ===\n");
			print_object_info(obj);
			*needs_rerender = true;
			return;
		}
		else if (keycode == KEY_G) /* decrease height */
		{
			obj->prop.cylinder.height -= 0.1;
			if (obj->prop.cylinder.height < 0.01)
				obj->prop.cylinder.height = 0.01;
			printf("\n=== Cylinder Height Changed ===\n");
			print_object_info(obj);
			*needs_rerender = true;
			return;
		}
	}
}

static void	handle_object_transform_rotation(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_object	*obj;
	t_matrix	*transform_update;
	t_matrix	*new_transform;
	double		step;

	if (!scene->selected_object || !scene->selected_object->data)
		return;
	if (!scene->translation_mode && !scene->rotation_mode)
		return;
	
	obj = (t_object *)scene->selected_object->data;
	step = 0.5;
	
	/* Translation mode */
	if (scene->translation_mode)
	{
		if (keycode == KEY_I) /* Y+ (up) */
			transform_update = translation(0, step, 0);
		else if (keycode == KEY_K) /* Y- (down) */
			transform_update = translation(0, -step, 0);
		else if (keycode == KEY_J) /* X- (left) */
			transform_update = translation(-step, 0, 0);
		else if (keycode == KEY_SEMICOLON) /* X+ (right) */
			transform_update = translation(step, 0, 0);
		else if (keycode == KEY_U) /* Z+ (forward) */
			transform_update = translation(0, 0, step);
		else if (keycode == KEY_M) /* Z- (backward) */
			transform_update = translation(0, 0, -step);
		else
			return;
		new_transform = matrix_product(transform_update, obj->transform);
		set_transform(obj, new_transform);
		free_matrix(transform_update);
		printf("\n=== Object Translated ===\n");
		print_object_info(obj);
		*needs_rerender = true;
	}
	/* Rotation mode (not for spheres) */
	else if (scene->rotation_mode && obj->type != SPHERE)
	{
		if (keycode == KEY_I) /* Rotate around X+ */
			transform_update = rotation_x(0.1);
		else if (keycode == KEY_K) /* Rotate around X- */
			transform_update = rotation_x(-0.1);
		else if (keycode == KEY_J) /* Rotate around Y- */
			transform_update = rotation_y(-0.1);
		else if (keycode == KEY_SEMICOLON) /* Rotate around Y+ */
			transform_update = rotation_y(0.1);
		else if (keycode == KEY_U) /* Rotate around Z+ */
			transform_update = rotation_z(0.1);
		else if (keycode == KEY_M) /* Rotate around Z- */
			transform_update = rotation_z(-0.1);
		else
			return;
		new_transform = matrix_product(obj->transform, transform_update);
		set_transform(obj, new_transform);
		free_matrix(transform_update);
		printf("\n=== Object Rotated ===\n");
		print_object_info(obj);
		*needs_rerender = true;
	}
	else if (scene->rotation_mode && obj->type == SPHERE)
	{
		printf("\nSpheres cannot be rotated.\n");
	}
}

static void	handle_light_transform(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_light	*light;
	double	step;

	if (!scene->selected_light || !scene->selected_light->data)
		return;
	if (!scene->translation_mode)
		return;
	
	light = (t_light *)scene->selected_light->data;
	step = 0.5;
	
	if (keycode == KEY_I) /* Y+ (up) */
		light->origin.y += step;
	else if (keycode == KEY_K) /* Y- (down) */
		light->origin.y -= step;
	else if (keycode == KEY_J) /* X- (left) */
		light->origin.x -= step;
	else if (keycode == KEY_SEMICOLON) /* X+ (right) */
		light->origin.x += step;
	else if (keycode == KEY_U) /* Z+ (forward) */
		light->origin.z += step;
	else if (keycode == KEY_M) /* Z- (backward) */
		light->origin.z -= step;
	else
		return;
	
	printf("\n=== Light Translated ===\n");
	printf("Light Position: (%.1f, %.1f, %.1f)\n",
		light->origin.x, light->origin.y, light->origin.z);
	*needs_rerender = true;
}

static void	handle_camera_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	if (keycode == KEY_W) 
		add_tuples(&scene->camera.from, &scene->camera.from,
			&scene->camera.orientation);
	else if (keycode == KEY_S) 
		subtract_tuples(&scene->camera.from, &scene->camera.from,
			&scene->camera.orientation);
	else if (keycode == KEY_A)
	{
		t_vector right;
		dot_cross(&right, &scene->camera.orientation, &scene->camera.up);
		subtract_tuples(&scene->camera.from, &scene->camera.from, &right);
	}
	else if (keycode == KEY_D) 
	{
		t_vector right;
		dot_cross(&right, &scene->camera.orientation, &scene->camera.up);
		add_tuples(&scene->camera.from, &scene->camera.from, &right);
	}
	else
		return ;
	*needs_rerender = true;
}

static void	handle_camera_rotation(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_matrix	*rot_m;

	if (keycode == KEY_LEFT)
		rot_m = rotation_y(0.1);
	else if (keycode == KEY_RIGHT)
		rot_m = rotation_y(-0.1); 
	else if (keycode == KEY_UP)
		rot_m = rotation_x(0.1); 
	else if (keycode == KEY_DOWN)
		rot_m = rotation_x(-0.1); 
	else
		return ;
	scene->camera.orientation = multiply_matrix_by_tuple(rot_m,
			scene->camera.orientation);
	free_matrix(rot_m);
	*needs_rerender = true;
}

int	handle_keypress(int keycode, t_scene *scene)
{
	bool	needs_rerender;

	needs_rerender = false;
	if (keycode == ESC_KEY)
		close_window(scene);
	
	/* Mode toggles */
	if (keycode == KEY_T)
	{
		scene->translation_mode = !scene->translation_mode;
		scene->rotation_mode = false; /* Disable rotation mode */
		printf("\n=== Translation Mode: %s ===\n",
			scene->translation_mode ? "ON" : "OFF");
		if (scene->translation_mode)
			printf("Use I/K (Y), J/; (X), U/M (Z) to translate selected object/light\n");
		return (0);
	}
	if (keycode == KEY_R)
	{
		scene->rotation_mode = !scene->rotation_mode;
		scene->translation_mode = false; /* Disable translation mode */
		printf("\n=== Rotation Mode: %s ===\n",
			scene->rotation_mode ? "ON" : "OFF");
		if (scene->rotation_mode)
			printf("Use I/K (X-axis), J/; (Y-axis), U/M (Z-axis) to rotate selected object\n");
		return (0);
	}
	
	/* Handle transforms/rotations in active mode */
	handle_object_transform_rotation(keycode, scene, &needs_rerender);
	handle_light_transform(keycode, scene, &needs_rerender);
	
	/* Standard controls */
	handle_camera_controls(keycode, scene, &needs_rerender);
	handle_object_controls(keycode, scene, &needs_rerender);
	handle_camera_rotation(keycode, scene, &needs_rerender);
	handle_light_controls(keycode, scene, &needs_rerender);
	
	if (needs_rerender)
	{
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
	return (0);
}

int	handle_mouse_scroll(int button, int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	/* change fov in radians (5 degrees step) and recompute camera internals */
	if (button == MOUSE_SCROLL_UP)
	{
		double	step = 5.0 * (M_PI / 180.0);
		scene->camera.fov -= step;
		if (scene->camera.fov < 1.0 * (M_PI / 180.0))
			scene->camera.fov = 1.0 * (M_PI / 180.0);
		camera_init(&scene->camera, WIDTH, HEIGHT, scene->camera.fov);
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		double	step = 5.0 * (M_PI / 180.0);
		scene->camera.fov += step;
		if (scene->camera.fov > 179.0 * (M_PI / 180.0))
			scene->camera.fov = 179.0 * (M_PI / 180.0);
		camera_init(&scene->camera, WIDTH, HEIGHT, scene->camera.fov);
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
	return (0);
}
