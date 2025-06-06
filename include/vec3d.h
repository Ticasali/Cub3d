/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:55:05 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 05:41:26 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

#define EPSILON 0.00001

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

t_vec3d	vec3d_add(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_sub(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_mul(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_div(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_scale(const t_vec3d a, const float b);
t_vec3d	vec3d_normalize(const t_vec3d a);
float	vec3d_dot(const t_vec3d a, const t_vec3d b);
float	vec3d_dist(const t_vec3d a, const t_vec3d b);
float	vec3d_sqrdist(const t_vec3d a, const t_vec3d b);
float	vec3d_len(const t_vec3d a);
float	vec3d_sqrlen(const t_vec3d a);
t_vec3d	vec3d_invert(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_cross(const t_vec3d a, const t_vec3d b);
int		vec3d_equal(const t_vec3d a, const t_vec3d b);
int		vec3d_iszero(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_rotate(const t_vec3d a, const float angle, const t_vec3d axis);
t_vec3d	vec3d_reflect(const t_vec3d a, const t_vec3d normal);
t_vec3d	vec3d_lerp(const t_vec3d a, const t_vec3d b, float t);
t_vec3d	vec3d_slerp(t_vec3d a, const t_vec3d b, float t);
t_vec3d	vec3d_project(const t_vec3d a, const t_vec3d b);
t_vec3d	vec3d_unproject(const t_vec3d a, const t_vec3d b);

#endif
