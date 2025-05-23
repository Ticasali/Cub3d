/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:13:04 by dderny            #+#    #+#             */
/*   Updated: 2025/05/11 14:43:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

inline t_vec3d	vec3d_div(const t_vec3d a, const t_vec3d b)
{
	if (b.x == 0 || b.y == 0 || b.z == 0)
		return ((t_vec3d){0, 0, 0});
	else
		return ((t_vec3d){
			a.x / b.x,
			a.y / b.y,
			a.z / b.z
		});
}
