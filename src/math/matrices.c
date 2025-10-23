/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/22 20:31:56 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

t_vector	matrix_to_tuple(t_matrix *final)
{
	t_vector	tuple;

	tuple.x = final->matrix[0][0];
	tuple.y = final->matrix[1][0];
	tuple.z = final->matrix[2][0];
	tuple.w = final->matrix[3][0];
	return (tuple);
}

t_vector	multiply_matrix_by_tuple(t_matrix *m, t_vector t)
{
	t_vector	result;

	result.x = m->matrix[0][0] * t.x + m->matrix[0][1] * t.y
		+ m->matrix[0][2] * t.z + m->matrix[0][3] * t.w;
	result.y = m->matrix[1][0] * t.x + m->matrix[1][1] * t.y
		+ m->matrix[1][2] * t.z + m->matrix[1][3] * t.w;
	result.z = m->matrix[2][0] * t.x + m->matrix[2][1] * t.y
		+ m->matrix[2][2] * t.z + m->matrix[2][3] * t.w;
	result.w = m->matrix[3][0] * t.x + m->matrix[3][1] * t.y
		+ m->matrix[3][2] * t.z + m->matrix[3][3] * t.w;
	return (result);
}
