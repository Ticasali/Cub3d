/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:15:58 by dderny            #+#    #+#             */
/*   Updated: 2025/05/11 14:30:41 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vec3d.h"

int is_point_in_plane(t_vec3d point, t_plane plane)
{
	t_vec3d crossabp;
	t_vec3d crossbcp;
	t_vec3d crosscdp;
	t_vec3d crossdap;
	
	crossabp = vec3d_cross(vec3d_sub(plane.b, plane.a),
		vec3d_sub(point, plane.a));
	crossbcp = vec3d_cross(vec3d_sub(plane.c, plane.b),
		vec3d_sub(point, plane.b));
	crosscdp = vec3d_cross(vec3d_sub(plane.d, plane.c),
		vec3d_sub(point, plane.c));
	crossdap = vec3d_cross(vec3d_sub(plane.a, plane.d),
		vec3d_sub(point, plane.d));
	if (vec3d_dot(crossabp, crossbcp) < 0
		|| vec3d_dot(crossbcp, crosscdp) < 0
		|| vec3d_dot(crosscdp, crossdap) < 0
		|| vec3d_dot(crossdap, crossabp) < 0)
		return (0);
	return (1);
}

int intersect_segment_plane(t_vec3d p1, t_vec3d p2, t_plane plane, t_vec3d *intersection)
{
	t_vec3d n = vec3d_cross(vec3d_sub(plane.b, plane.a), vec3d_sub(plane.c, plane.a));
	double d = vec3d_dot(n, plane.a);
	double t = (d - vec3d_dot(n, p1)) / vec3d_dot(n, vec3d_sub(p2, p1));
	if (t < 0 || t > 1)
		return (0);
	*intersection = vec3d_add(p1, vec3d_scale(vec3d_sub(p2, p1), t));
	return (is_point_in_plane(*intersection, plane));
}