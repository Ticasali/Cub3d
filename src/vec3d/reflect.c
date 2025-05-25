/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:19:02 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 05:41:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

inline t_vec3d	vec3d_reflect(const t_vec3d a, const t_vec3d normal)
{
	float		dot;

	dot = vec3d_dot(a, normal);
	return ((t_vec3d){
		a.x - 2 * dot * normal.x,
		a.y - 2 * dot * normal.y,
		a.z - 2 * dot * normal.z
	});
}
