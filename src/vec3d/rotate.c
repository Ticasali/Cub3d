/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:17:50 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 05:41:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include <math.h>

inline t_vec3d	vec3d_rotate(const t_vec3d vec, const float angle, const t_vec3d axis)
{
	float		cos_angle;
	float		sin_angle;
	float		dot_product;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	dot_product = vec3d_dot(vec, axis);
	return ((t_vec3d){
		vec.x * cos_angle + (1 - cos_angle) * dot_product
			* axis.x + sin_angle * (axis.y * vec.z - axis.z * vec.y),
		vec.y * cos_angle + (1 - cos_angle) * dot_product
			* axis.y + sin_angle * (axis.z * vec.x - axis.x * vec.z),
		vec.z * cos_angle + (1 - cos_angle) * dot_product
			* axis.z + sin_angle * (axis.x * vec.y - axis.y * vec.x)
	});
}
