/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/16 16:58:20 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_allocation	**get_alloc_head(void)
{
	static t_allocation	*head = NULL;

	return (&head);
}

void	*safe_malloc(size_t size, t_alloc_type u_type)
{
	t_allocation	**head;
	t_allocation	*new_alloc;

	new_alloc = malloc(sizeof(t_allocation));
	if (!new_alloc)
		return (print_error("malloc error"), NULL);
	new_alloc->ptr = malloc(size);
	if (!new_alloc->ptr)
	{
		free(new_alloc);
		return (print_error("malloc error"), NULL);
	}
	new_alloc->type = u_type;
	head = get_alloc_head();
	new_alloc->next = *head;
	*head = new_alloc;
	return (new_alloc->ptr);
} 
void	free_all(void)
{
	t_allocation	**head;
	t_allocation	*alloc;
	t_allocation	*next;

	head = get_alloc_head();
	alloc = *head;
	while (alloc)
	{
		next = alloc->next;
		if (alloc->type == ALLOC_TYPE_MTX)
			free_matrix(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_OBJECT)
			free_object(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_LIGHT)
			free_light(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_SCENE)
			free_scene((t_scene *)alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_STRING
			|| alloc->type == ALLOC_TYPE_GENERIC)
			free(alloc->ptr);
		free(alloc);
		alloc = next;
	}
	*head = NULL;
}

void	free_matrix(t_matrix *m)
{
	int	i;

	i = 0;
	while (i < m->row)
	{
		free(m->matrix[i]);
		i++;
	}
	free(m->matrix);
	free(m);
}

void	free_object(void *obj_ptr)
{
	t_object *obj;

	obj = (t_object *)obj_ptr;
	if (obj)
	{
		if (obj->transform)
			free_matrix(obj->transform);
		if (obj->inverse_transform)
			free_matrix(obj->inverse_transform);
		if (obj->transpose_inverse_transform)
			free_matrix(obj->transpose_inverse_transform);
		free(obj);
	}
}

void	free_light(void *light_ptr)
{
	t_light	*light;

	light = (t_light *)light_ptr;
	if (light)
		free(light);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->camera.transform)
		free_matrix(scene->camera.transform);
	if (scene->lights)
		ft_lstclear(&scene->lights, free_light);
	if (scene->objects)
		ft_lstclear(&scene->objects, free_object);
	if (scene->mlx.img_ptr)
		mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	if (scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	if (scene->mlx.mlx_ptr)
	{
		mlx_destroy_display(scene->mlx.mlx_ptr);
		free(scene->mlx.mlx_ptr);
	}
	free(scene);
}