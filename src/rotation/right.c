/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 04:42:48 by dderny            #+#    #+#             */
/*   Updated: 2025/05/25 22:21:22 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include <math.h>

t_vec3d	rot_right(t_rot r)
{
	t_vec3d	rot;

	rot.x = cosf(r.z * (M_PI / 180.0f)) * cosf(r.y * (M_PI / 180.0f));
	rot.y = sinf(r.z * (M_PI / 180.0f)) * cosf(r.y * (M_PI / 180.0f));
	rot.z = sinf(r.y * (M_PI / 180.0f));
	return (rot);
}