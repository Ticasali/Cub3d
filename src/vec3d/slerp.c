/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slerp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:18:40 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 05:41:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include <math.h>

t_vec3d	vec3d_slerp(t_vec3d a, t_vec3d b, float t)
{
	t_vec3d	result;
	float		theta;
	float		sin_theta;
	float		sin_atheta;
	float		sin_btheta;

	if (t < 0)
		t = 0;
	else if (t > 1)
		t = 1;
	if (vec3d_equal(a, b))
		return (a);
	theta = acos(vec3d_dot(a, b) / (vec3d_len(a) * vec3d_len(b)));
	sin_theta = sin(theta);
	sin_atheta = sin((1 - t) * theta);
	sin_btheta = sin(t * theta);
	result.x = (sin_atheta * a.x + sin_btheta * b.x) / sin_theta;
	result.y = (sin_atheta * a.y + sin_btheta * b.y) / sin_theta;
	result.z = (sin_atheta * a.z + sin_btheta * b.z) / sin_theta;
	return (result);
}
