/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:04:17 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 22:16:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H
# include "vec3d.h"

typedef t_vec3d t_rotation;

t_rotation	rotation_create(double x, double y, double z);
t_rotation	rotation_add(t_rotation a, t_rotation b);
t_rotation	rotation_sub(t_rotation a, t_rotation b);
t_rotation	rotation_mult(t_rotation a, t_rotation b);
t_rotation	rotation_div(t_rotation a, t_rotation b);
t_rotation	rotation_scale(t_rotation a, double b);
t_vec3d		rotation_tonormal(t_rotation r);

#endif
