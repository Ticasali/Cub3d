/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:13:04 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 02:13:09 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

t_vec3d	vec3d_div(t_vec3d a, t_vec3d b)
{
	t_vec3d	result;

	if (b.x == 0 || b.y == 0 || b.z == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	else
	{
		result.x = a.x / b.x;
		result.y = a.y / b.y;
		result.z = a.z / b.z;
	}
	return (result);
}
