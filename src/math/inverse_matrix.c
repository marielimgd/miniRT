/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:19:57 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:19:57 by jhualves         ###   ########.fr       */
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

	sub = create_matrix(a->collum - 1, a->row - 1);
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
	int			row;
	int			col;

	det = determinant(m);
	if (is_equal(det, 0))
	{
		print_error("Matrix is not invertible");
		return (NULL);
	}
	inv = create_matrix(m->collum, m->row);
	row = 0;
	while (row < m->row)
	{
		col = 0;
		while (col < m->collum)
		{
			inv->matrix[col][row] = cofactor(m, row, col) / det;
			col++;
		}
		row++;
	}
	return (inv);
}
