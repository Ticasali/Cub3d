/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iszero.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:17:56 by dderny            #+#    #+#             */
/*   Updated: 2025/05/11 14:43:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include <math.h>

inline int	vec3d_iszero(const t_vec3d a, const t_vec3d b)
{
	return (fabs(a.x) < EPSILON && fabs(a.y) < EPSILON && fabs(a.z) < EPSILON
		&& fabs(b.x) < EPSILON && fabs(b.y) < EPSILON && fabs(b.z) < EPSILON);
}
