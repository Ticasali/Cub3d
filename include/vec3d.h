/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:55:05 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 02:21:57 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

#define EPSILON 0.00001

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}	t_vec3d;

t_vec3d	vec3d_add(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_sub(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_mul(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_div(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_scale(t_vec3d a, double b);
t_vec3d	vec3d_normalize(t_vec3d a);
double	vec3d_dot(t_vec3d a, t_vec3d b);
double	vec3d_dist(t_vec3d a, t_vec3d b);
double	vec3d_sqrdist(t_vec3d a, t_vec3d b);
double	vec3d_len(t_vec3d a);
double	vec3d_sqrlen(t_vec3d a);
t_vec3d	vec3d_invert(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_cross(t_vec3d a, t_vec3d b);
int		vec3d_equal(t_vec3d a, t_vec3d b);
int		vec3d_iszero(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_rotate(t_vec3d a, double angle, t_vec3d axis);
t_vec3d	vec3d_reflect(t_vec3d a, t_vec3d normal);
t_vec3d	vec3d_lerp(t_vec3d a, t_vec3d b, double t);
t_vec3d	vec3d_slerp(t_vec3d a, t_vec3d b, double t);
t_vec3d	vec3d_project(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_unproject(t_vec3d a, t_vec3d b);

#endif
