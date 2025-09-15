/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:24:43 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/15 19:27:57 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*rotation_x(double radians)
{
	t_matrix	*m;

	m = identity_matrix();
	m->matrix[1][1] = cos(radians);
	m->matrix[1][2] = -sin(radians);
	m->matrix[2][1] = sin(radians);
	m->matrix[2][2] = cos(radians);
	return (m);
}

t_matrix	*rotation_y(double radians)
{
	t_matrix	*m;

	m = identity_matrix();
	m->matrix[0][0] = cos(radians);
	m->matrix[0][2] = sin(radians);
	m->matrix[2][0] = -sin(radians);
	m->matrix[2][2] = cos(radians);
	return (m);
}

t_matrix	*rotation_z(double radians)
{
	t_matrix	*m;

	m = identity_matrix();
	m->matrix[0][0] = cos(radians);
	m->matrix[0][1] = -sin(radians);
	m->matrix[1][0] = sin(radians);
	m->matrix[1][1] = cos(radians);
	return (m);
}

static void	fill_rotation_matrix(t_matrix *m, t_vector axis, double trig[3])
{
	m->matrix[0][0] = trig[2] * axis.x * axis.x + trig[0];
	m->matrix[0][1] = trig[2] * axis.x * axis.y - trig[1] * axis.z;
	m->matrix[0][2] = trig[2] * axis.x * axis.z + trig[1] * axis.y;
	m->matrix[1][0] = trig[2] * axis.x * axis.y + trig[1] * axis.z;
	m->matrix[1][1] = trig[2] * axis.y * axis.y + trig[0];
	m->matrix[1][2] = trig[2] * axis.y * axis.z - trig[1] * axis.x;
	m->matrix[2][0] = trig[2] * axis.x * axis.z - trig[1] * axis.y;
	m->matrix[2][1] = trig[2] * axis.y * axis.z + trig[1] * axis.x;
	m->matrix[2][2] = trig[2] * axis.z * axis.z + trig[0];
}

t_matrix	*rotation_from_orientation(t_vector orientation)
{
	t_matrix	*m;
	t_vector	up;
	t_vector	axis;
	double		angle;
	double		trig[3];

	up = create_vector(0, 1, 0);
	normalization(&orientation, &orientation);
	dot_cross(&axis, &up, &orientation);
	if (is_equal(get_magnitude(&axis), 0))
	{
		if (is_equal(dot_product(&up, &orientation), -1))
			return (rotation_x(M_PI));
		return (identity_matrix());
	}
	normalization(&axis, &axis);
	angle = acos(dot_product(&up, &orientation));
	m = identity_matrix();
	trig[0] = cos(angle);
	trig[1] = sin(angle);
	trig[2] = 1.0 - trig[0];
	fill_rotation_matrix(m, axis, trig);
	return (m);
}
