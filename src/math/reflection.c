/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:53:45 by marieli           #+#    #+#             */
/*   Updated: 2025/09/13 19:56:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reflect(t_vector *result, t_vector *in, t_vector *normal)
{
	t_vector	scaled_normal;
	double		dot_in_normal;

	dot_in_normal = dot_product(in, normal);
	scale_tuples_product(&scaled_normal, normal, 2 * dot_in_normal);
	subtract_tuples(result, in, &scaled_normal);
}
