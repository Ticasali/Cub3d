/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:23:48 by dderny            #+#    #+#             */
/*   Updated: 2025/05/12 15:18:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"
#include "vec3d.h"
#include "libft.h"
#include <stdio.h>

int plane_colors[6] = {
	0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF
};
t_plane scene_planes[6] = {
	{(t_vec3d){-50, -50, 0}, (t_vec3d){50, -50, 0}, (t_vec3d){50, 50, 0}, (t_vec3d){-50, 50, 0}},
	{(t_vec3d){-50, -50, 0}, (t_vec3d){-50, 50, 0}, (t_vec3d){-50, 50, -50}, (t_vec3d){-50, -50, -50}},
	{(t_vec3d){50, -50, 0}, (t_vec3d){50, 50, 0}, (t_vec3d){50, 50, -50}, (t_vec3d){50, -50, -50}},
	{(t_vec3d){-50, -50, -50}, (t_vec3d){50, -50, -50}, (t_vec3d){50, 50, -50}, (t_vec3d){-50, 50, -50}},
	{(t_vec3d){-50, -50, 0}, (t_vec3d){-50, -50, -50}, (t_vec3d){50, -50, -50}, (t_vec3d){50, -50, 0}},
	{(t_vec3d){-50, 50, 0}, (t_vec3d){-50, 50, -50}, (t_vec3d){50, 50, -50}, (t_vec3d){50, 50, 0}}
};

static void	trace_rays(t_cub3d *cub3d, int x)
{
	int		i;
	float 	dist;
	int		size;
	t_vec3d intersection;
	t_color c;

	t_vec3d pos = (t_vec3d){
		2 * x / (double)cub3d->width - 1,
		0,
		0
	};
	t_vec3d ray_dir = {
		cub3d->camera.dir.x + cub3d->camera.plane.x * pos.x,
		cub3d->camera.dir.y + cub3d->camera.plane.y * pos.x,
		0
	};
	ray_dir = vec3d_normalize(ray_dir);	
	i = 0;
	while (i < 6)
	{
		t_vec3d cam_pos_b = vec3d_add(cub3d->camera.pos,  vec3d_scale(ray_dir, 99999));
		if (intersect_segment_plane(cub3d->camera.pos, cam_pos_b, scene_planes[i], &intersection))
		{
			dist = vec3d_dist(cub3d->camera.pos, intersection);
			size = cub3d->height / dist * 25;
			c.rgb = plane_colors[i];
			dist = ft_fclamp(1 - dist / 150, 0.1, 1);
			c.r *= dist;
			c.g *= dist;
			c.b *= dist;

			int smax = ft_min(size / 2, cub3d->height / 2);
			int y = cub3d->height / 2 - smax;
			while (y < cub3d->height / 2 + smax)
			{
				put_pixel_color(cub3d->buffer, x, y, c.rgb);
				y++;
			}
			break;
		}
		i++;
	}
}

void	tick_update(t_cub3d *cub3d)
{
	int	x;
	
	ft_bzero(cub3d->buffer.data, cub3d->buffer.size * sizeof(u_int));
	x = 0;
	while (x < cub3d->width)
	{
		trace_rays(cub3d, x);
		x++;
	}

	if (get_key_state(cub3d, 'q') == KEY_DOWN)
	{
		cub3d->camera.dir = vec3d_rotate(cub3d->camera.dir, -1 * cub3d->delta_t, (t_vec3d){0, 0, 1});	
		cub3d->camera.plane = vec3d_rotate(cub3d->camera.plane, -1 * cub3d->delta_t, (t_vec3d){0, 0, 1});
	}
	if (get_key_state(cub3d, 'e') == KEY_DOWN)
	{
		cub3d->camera.dir = vec3d_rotate(cub3d->camera.dir, 1 * cub3d->delta_t, (t_vec3d){0, 0, 1});	
		cub3d->camera.plane = vec3d_rotate(cub3d->camera.plane, 1 * cub3d->delta_t, (t_vec3d){0, 0, 1});
	}
	if (get_key_state(cub3d, 'w') == KEY_DOWN)
	{
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos, vec3d_scale(cub3d->camera.dir, 10 * cub3d->delta_t));
	}
	if (get_key_state(cub3d, 's') == KEY_DOWN)
	{
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos, vec3d_scale(cub3d->camera.dir, -10 * cub3d->delta_t));
	}
}