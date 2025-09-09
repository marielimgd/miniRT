/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:26:48 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/09 14:56:22 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	*submatrix(t_matrix *a, int row_to_remove, int col_to_remove)
{
	t_matrix	*sub;
	int			r;
	int			c;
	int			sub_r;
	int			sub_c;

	sub = create_matrix(a->row - 1, a->collum - 1);
	sub_r = 0;
	r = -1;
	while (++r < a->row)
	{
		if (r == row_to_remove)
			continue ;
		sub_c = 0;
		c = -1;
		while (++c < a->collum)
		{
			if (c != col_to_remove)
				sub->matrix[sub_r][sub_c++] = a->matrix[r][c];
		}
		sub_r++;
	}
	return (sub);
}

double	cofactor(t_matrix *m, int row, int col)
{
	double		minor_det;
	t_matrix	*sub;

	sub = submatrix(m, row, col);
	minor_det = determinant(sub);
	free_matrix(sub);
	if ((row + col) % 2 == 1)
		return (-minor_det);
	return (minor_det);
}

double	determinant(t_matrix *m)
{
	double		det;
	int			c;

	det = 0;
	if (m->row == 2)
		return (m->matrix[0][0] * m->matrix[1][1]
			- m->matrix[0][1] * m->matrix[1][0]);
	c = 0;
	while (c < m->collum)
	{
		det = det + m->matrix[0][c] * cofactor(m, 0, c);
		c++;
	}
	return (det);
}


t_matrix	*inverse_matrix(t_matrix *m)
{
	t_matrix	*inv;
	double		det;
	double		a[16];
	double		b[16];

	inv = create_matrix(4, 4);
	a[0] = m->matrix[0][0]; a[1] = m->matrix[0][1]; a[2] = m->matrix[0][2]; a[3] = m->matrix[0][3];
	a[4] = m->matrix[1][0]; a[5] = m->matrix[1][1]; a[6] = m->matrix[1][2]; a[7] = m->matrix[1][3];
	a[8] = m->matrix[2][0]; a[9] = m->matrix[2][1]; a[10] = m->matrix[2][2]; a[11] = m->matrix[2][3];
	a[12] = m->matrix[3][0]; a[13] = m->matrix[3][1]; a[14] = m->matrix[3][2]; a[15] = m->matrix[3][3];

	b[0] = a[5] * a[10] * a[15] - a[5] * a[11] * a[14] - a[9] * a[6] * a[15] + a[9] * a[7] * a[14] + a[13] * a[6] * a[11] - a[13] * a[7] * a[10];
	b[1] = -a[1] * a[10] * a[15] + a[1] * a[11] * a[14] + a[9] * a[2] * a[15] - a[9] * a[3] * a[14] - a[13] * a[2] * a[11] + a[13] * a[3] * a[10];
	b[2] = a[1] * a[6] * a[15] - a[1] * a[7] * a[14] - a[5] * a[2] * a[15] + a[5] * a[3] * a[14] + a[13] * a[2] * a[7] - a[13] * a[3] * a[6];
	b[3] = -a[1] * a[6] * a[11] + a[1] * a[7] * a[10] + a[5] * a[2] * a[11] - a[5] * a[3] * a[10] - a[9] * a[2] * a[7] + a[9] * a[3] * a[6];
	b[4] = -a[4] * a[10] * a[15] + a[4] * a[11] * a[14] + a[8] * a[6] * a[15] - a[8] * a[7] * a[14] - a[12] * a[6] * a[11] + a[12] * a[7] * a[10];
	b[5] = a[0] * a[10] * a[15] - a[0] * a[11] * a[14] - a[8] * a[2] * a[15] + a[8] * a[3] * a[14] + a[12] * a[2] * a[11] - a[12] * a[3] * a[10];
	b[6] = -a[0] * a[6] * a[15] + a[0] * a[7] * a[14] + a[4] * a[2] * a[15] - a[4] * a[3] * a[14] - a[12] * a[2] * a[7] + a[12] * a[3] * a[6];
	b[7] = a[0] * a[6] * a[11] - a[0] * a[7] * a[10] - a[4] * a[2] * a[11] + a[4] * a[3] * a[10] + a[8] * a[2] * a[7] - a[8] * a[3] * a[6];
	b[8] = a[4] * a[9] * a[15] - a[4] * a[11] * a[13] - a[8] * a[5] * a[15] + a[8] * a[7] * a[13] + a[12] * a[5] * a[11] - a[12] * a[7] * a[9];
	b[9] = -a[0] * a[9] * a[15] + a[0] * a[11] * a[13] + a[8] * a[1] * a[15] - a[8] * a[3] * a[13] - a[12] * a[1] * a[11] + a[12] * a[3] * a[9];
	b[10] = a[0] * a[5] * a[15] - a[0] * a[7] * a[13] - a[4] * a[1] * a[15] + a[4] * a[3] * a[13] + a[12] * a[1] * a[7] - a[12] * a[3] * a[5];
	b[11] = -a[0] * a[5] * a[11] + a[0] * a[7] * a[9] + a[4] * a[1] * a[11] - a[4] * a[3] * a[9] - a[8] * a[1] * a[7] + a[8] * a[3] * a[5];
	b[12] = -a[4] * a[9] * a[14] + a[4] * a[10] * a[13] + a[8] * a[5] * a[14] - a[8] * a[6] * a[13] - a[12] * a[5] * a[10] + a[12] * a[6] * a[9];
	b[13] = a[0] * a[9] * a[14] - a[0] * a[10] * a[13] - a[8] * a[1] * a[14] + a[8] * a[2] * a[13] + a[12] * a[1] * a[10] - a[12] * a[2] * a[9];
	b[14] = -a[0] * a[5] * a[14] + a[0] * a[6] * a[13] + a[4] * a[1] * a[14] - a[4] * a[2] * a[13] - a[12] * a[1] * a[6] + a[12] * a[2] * a[5];
	b[15] = a[0] * a[5] * a[10] - a[0] * a[6] * a[9] - a[4] * a[1] * a[10] + a[4] * a[2] * a[9] + a[8] * a[1] * a[6] - a[8] * a[2] * a[5];

det = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
	if (is_equal(det, 0))
	{
		free_matrix(inv);
		print_error("Matrix is not invertible");
		return (NULL);
	}
	det = 1.0 / det;

	inv->matrix[0][0] = b[0] * det;
	inv->matrix[0][1] = b[4] * det;
	inv->matrix[0][2] = b[8] * det;
	inv->matrix[0][3] = b[12] * det;
	inv->matrix[1][0] = b[1] * det;
	inv->matrix[1][1] = b[5] * det;
	inv->matrix[1][2] = b[9] * det;
	inv->matrix[1][3] = b[13] * det;
	inv->matrix[2][0] = b[2] * det;
	inv->matrix[2][1] = b[6] * det;
	inv->matrix[2][2] = b[10] * det;
	inv->matrix[2][3] = b[11] * det;
	inv->matrix[3][0] = b[3] * det;
	inv->matrix[3][1] = b[7] * det;
	inv->matrix[3][2] = b[14] * det;
	inv->matrix[3][3] = b[15] * det;

	return (inv);
}
