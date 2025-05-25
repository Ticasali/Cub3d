/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 04:43:05 by dderny            #+#    #+#             */
/*   Updated: 2025/05/25 22:16:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include <math.h>

t_vec3d	rot_forward(t_rot r)
{
	t_vec3d	rot;

	rot.x = sinf(r.z * (M_PI / 180.0f)) * cosf(r.x * (M_PI / 180.0f));
	rot.y = cosf(r.z * (M_PI / 180.0f)) * cosf(r.x * (M_PI / 180.0f));
	rot.z = sinf(r.x * (M_PI / 180.0f));
	return (rot);
}