/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:17:26 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 02:17:45 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include <math.h>

int	vec3d_equal(t_vec3d a, t_vec3d b)
{
	return (fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON
		&& fabs(a.z - b.z) < EPSILON);
}
