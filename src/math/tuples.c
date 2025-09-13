/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:22:46 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/13 16:53:45 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

void	add_tuples(t_vector *result, t_vector *a, t_vector *b)
{
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
	result->w = a->w + b->w;
}

void	subtract_tuples(t_vector *result, t_vector *a, t_vector *b)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	result->w = a->w - b->w;
}

void	scale_tuples_product(t_vector *result, t_vector *v, double scale)
{
	result->x = v->x * scale;
	result->y = v->y * scale;
	result->z = v->z * scale;
	result->w = v->w * scale;
}
