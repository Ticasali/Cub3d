/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 06:34:42 by dderny            #+#    #+#             */
/*   Updated: 2025/05/25 05:34:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include <math.h>

t_vec3d	rot_up(t_rot r)
{
	t_vec3d	rot;

	rot.x = cosf(r.z * (M_PI / 180.0f)) * sinf(r.x * (M_PI / 180.0f));
	rot.y = sinf(r.z * (M_PI / 180.0f)) * sinf(r.x * (M_PI / 180.0f));
	rot.z = cosf(r.x * (M_PI / 180.0f));
	return (rot);
}