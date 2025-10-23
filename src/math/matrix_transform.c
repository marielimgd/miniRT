/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:30:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:30:00 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*translation(double x, double y, double z)
{
	t_matrix	*final;

	final = identity_matrix();
	final->matrix[0][3] = x;
	final->matrix[1][3] = y;
	final->matrix[2][3] = z;
	return (final);
}

t_matrix	*scaling(double x, double y, double z)
{
	t_matrix	*final;

	final = identity_matrix();
	final->matrix[0][0] = x;
	final->matrix[1][1] = y;
	final->matrix[2][2] = z;
	return (final);
}

double	determinante(t_matrix *a)
{
	double	det;

	if (a->row != 2 || a->collum != 2)
		print_error("Not possible find submatrix");
	det = (a->matrix[0][0] * a->matrix[1][1])
		- (a->matrix[0][1] * a->matrix[1][0]);
	return (det);
}
