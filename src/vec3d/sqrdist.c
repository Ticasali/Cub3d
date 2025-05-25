/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrdist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:17:00 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 05:41:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

inline float	vec3d_sqrdist(const t_vec3d a, const t_vec3d b)
{
	return (vec3d_sqrlen(vec3d_sub(a, b)));
}
