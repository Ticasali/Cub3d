/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:41:56 by dderny            #+#    #+#             */
/*   Updated: 2025/05/12 13:23:50 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "libft.h"
#include "vec3d.h"
#include <math.h>

inline void put_pixel_color(const t_oimg img, const int x, const int y, const u_int color)
{
	img.data[y * img.size_line + x] = color;
}

void draw_line(const t_oimg img, const t_vec3d p1, const t_vec3d p2, const u_int color)
{
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;
	double x = p1.x;
	double y = p1.y;

	for (int i = 0; i <= steps; i++)
	{
		if (x < 0 || x >= img.width || y < 0 || y >= img.height)
			break;
		put_pixel_color(img, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void draw_square(const t_oimg img, const t_vec3d p1, const t_vec3d p2, const u_int color)
{
	int x;
	int y;
	int x_end;
	int y_end;
	
	x = ft_clamp(p1.x, 0, img.width - 1);
	y = ft_clamp(p1.y, 0, img.height - 1);
	x_end = ft_clamp(p2.x, 0, img.width - 1);
	y_end = ft_clamp(p2.y, 0, img.height - 1);
	while (y < y_end)
	{
		ft_memset(img.data + y * img.size + x, color, (x_end - x) * sizeof(u_int));
		y++;
	}
}
