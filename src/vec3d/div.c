/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:13:04 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 01:24:34 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

inline t_vec3d	vec3d_div(const t_vec3d a, const t_vec3d b)
{
	t_vec3d	res;

	res = a;
	if (b.x == 0)
		res.x = 0;
	else
	 	res.x /= b.x;
	if (b.y == 0)
		res.y = 0;
	else
	 	res.y /= b.y;
	if (b.z == 0)
		res.z = 0;
	else
	 	res.z /= b.z;
	return (res);
}
