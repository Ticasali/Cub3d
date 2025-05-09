/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:55:05 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 02:04:09 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vec3d.h"

typedef struct s_matrix
{
	double	**m;
	int		rows;
	int		cols;
}	t_matrix;

t_matrix	*matrix_create(int rows, int cols);
void		matrix_destroy(t_matrix *matrix);
t_matrix	*matrix_identity(int size);
t_matrix	*matrix_add(t_matrix *a, t_matrix *b);
t_matrix	*matrix_sub(t_matrix *a, t_matrix *b);
t_matrix	*matrix_mult(t_matrix *a, t_matrix *b);
t_matrix	*matrix_scale(t_matrix *a, double b);
t_matrix	*matrix_transpose(t_matrix *a);
t_matrix	*matrix_inverse(t_matrix *a);
t_matrix	*matrix_rotate(t_matrix *a, double angle, t_vec3d axis);
t_matrix	*matrix_translate(t_matrix *a, t_vec3d translation);

#endif
