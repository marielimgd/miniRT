/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuplas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/02 19:50:48 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "scene.h"

void	add_vector_to_points(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x + point->x;
	result->y = vector->y + point->y;
	result->z = vector->z + point->z;
	result->w = vector->w + point->w;
}

void	add_vector_to_vector(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x + point->x;
	result->y = vector->y + point->y;
	result->z = vector->z + point->z;
	result->w = vector->w + point->w;
	return (result);
}

void	subtract_vector_to_points(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x - point->x;
	result->y = vector->y - point->y;
	result->z = vector->z - point->z;
	result->w = vector->w - point->w;
}

void	subtract_vector_of_vector(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x - point->x;
	result->y = vector->y - point->y;
	result->z = vector->z - point->z;
	result->w = vector->w - point->w;
}

void	subtract_point_of_point(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x - point->x;
	result->y = vector->y - point->y;
	result->z = vector->z - point->z;
	result->w = vector->w - point->w;
}

void	subtract_vector_of_point(t_vector *vector, t_vector *point)
{
	t_vector	*result;
	
	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector->x - point->x;
	result->y = vector->y - point->y;
	result->z = vector->z - point->z;
	result->w = vector->w - point->w;
}
