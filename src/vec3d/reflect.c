/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:19:02 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 02:19:26 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

t_vec3d	vec3d_reflect(t_vec3d a, t_vec3d normal)
{
	t_vec3d	result;
	double		dot;

	dot = vec3d_dot(a, normal);
	result.x = a.x - 2 * dot * normal.x;
	result.y = a.y - 2 * dot * normal.y;
	result.z = a.z - 2 * dot * normal.z;
	return (result);
}
