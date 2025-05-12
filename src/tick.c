/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:23:48 by dderny            #+#    #+#             */
/*   Updated: 2025/05/12 13:20:05 by dderny           ###   ########.fr       */
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

static void	trace_rays(t_cub3d *cub3d, int y)
{
	int		i;
	int 	dist;
	int		size;
	t_vec3d intersection;
	t_color c;

	t_vec3d pos = (t_vec3d){
		0,
		2 * y / (double)cub3d->height - 1,
		0
	};
	t_vec3d ray_dir = {
		cub3d->camera.dir.x + cub3d->camera.plane.x * pos.y,
		cub3d->camera.dir.y + cub3d->camera.plane.y * pos.y,
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
			size = cub3d->height / dist * 50;
			c.rgb = plane_colors[i];
			dist /= 150;
			c.r *= ft_fclamp(1 - dist, 0, 1);
			c.g *= ft_fclamp(1 - dist, 0, 1);
			c.b *= ft_fclamp(1 - dist, 0, 1);
			ft_memsetint(cub3d->buffer.data + (y * cub3d->buffer.size_line + cub3d->width / 2 - size / 2), c.rgb, ft_min(size / 2, cub3d->width / 2) * 2);
			break;
		}
		i++;
	}
}

void	tick_update(t_cub3d *cub3d)
{
	int	y;
	
	ft_bzero(cub3d->buffer.data, cub3d->buffer.size * sizeof(u_int));
	y = 0;
	while (y < cub3d->height)
	{
		trace_rays(cub3d, y);
		y++;
	}

	if (get_key_state(cub3d, 'w') == KEY_DOWN)
	{
		cub3d->camera.dir = vec3d_rotate(cub3d->camera.dir, 1 * cub3d->delta_t, (t_vec3d){1, 0, 0});	
		cub3d->camera.plane = vec3d_rotate(cub3d->camera.plane, 1 * cub3d->delta_t, (t_vec3d){1, 0, 0});
	}
	if (get_key_state(cub3d, 's') == KEY_DOWN)
	{
		cub3d->camera.dir = vec3d_rotate(cub3d->camera.dir, -1 * cub3d->delta_t, (t_vec3d){1, 0, 0});	
		cub3d->camera.plane = vec3d_rotate(cub3d->camera.plane, -1 * cub3d->delta_t, (t_vec3d){1, 0, 0});
	}
	if (get_key_state(cub3d, 'a') == KEY_DOWN)
	{
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos, vec3d_scale(cub3d->camera.dir, 10 * cub3d->delta_t));
	}
	if (get_key_state(cub3d, 'd') == KEY_DOWN)
	{
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos, vec3d_scale(cub3d->camera.dir, -10 * cub3d->delta_t));
	}
}