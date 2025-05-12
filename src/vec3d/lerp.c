/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:18:26 by dderny            #+#    #+#             */
/*   Updated: 2025/05/11 14:43:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

inline t_vec3d	vec3d_lerp(const t_vec3d a, const t_vec3d b, double t)
{
	if (t < 0)
		t = 0;
	else if (t > 1)
		t = 1;
	return ((t_vec3d){
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	});
}
