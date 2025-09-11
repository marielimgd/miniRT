/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:53:45 by marieli           #+#    #+#             */
/*   Updated: 2025/09/11 19:54:29 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*reflect(t_vector in, t_vector normal)
{
	t_vector	*scaled_normal;
	t_vector	*result;
	double		dot_in_normal;

	dot_in_normal = dot_product(&in, &normal);
	scaled_normal = scale_tuples_product(&normal, 2 * dot_in_normal);
	result = subtract_tuples(&in, scaled_normal);

	free(scaled_normal);
	return (result);
}