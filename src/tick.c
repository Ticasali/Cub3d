/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:23:48 by dderny            #+#    #+#             */
/*   Updated: 2025/05/25 22:23:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"
#include "rotation.h"
#include "vec3d.h"
#include "libft.h"
#include <X11/Xutil.h>
#include <math.h>
#include <stdio.h>

static void	draw_wall(t_cub3d *cub3d, t_vec3d pos_a, t_vec3d pos_b, int	ty_a, int ty_b)
{
	int	color = (t_color){.r = 155, .g = 50, .b = 0}.rgb;
	int	dx = pos_b.x - pos_a.x;
	if (dx == 0)
		dx = 1;
	int	dy = pos_b.y - pos_a.y;
	int	tdy = ty_b - ty_a;
	int	x = pos_a.x;
	int	y;
	
	while (x < pos_b.x)
	{
		y = dy * ((x - pos_a.x + 0.5) / dx) + pos_a.y;
		if (x > 0 && x < cub3d->width && y > 0 && y < cub3d->height)
			put_pixel_color(cub3d->buffer, x, y, color);
		y = tdy * ((x - pos_a.x + 0.5) / dx) + ty_a;
		if (x > 0 && x < cub3d->width && y > 0 && y < cub3d->height)
			put_pixel_color(cub3d->buffer, x, y, color);
		x++;
	}	
}

static t_vec3d	to_screen(t_cub3d *cub3d, t_vec3d wpos)
{
	return ((t_vec3d) {
		wpos.x * 500 / wpos.y + cub3d->width / 2.,
		wpos.z * 500 / wpos.y + cub3d->height / 2.,
		0
	});
}

static void	test_wall(t_cub3d *cub3d, t_vec3d wpos_a, t_vec3d wpos_b)
{
	wpos_a = vec3d_sub(wpos_a, cub3d->camera.pos);
	wpos_b = vec3d_sub(wpos_b, cub3d->camera.pos);

	float cam_cos = cosf(cub3d->camera.rot.z * (M_PI / 180.0f));
	float cam_sin = sinf(cub3d->camera.rot.z * (M_PI / 180.0f));
	t_vec3d spos[4];
	
	spos[0] = (t_vec3d) {
		wpos_a.x * cam_cos - wpos_a.y * cam_sin,
		wpos_a.y * cam_cos + wpos_a.x * cam_sin,
		-cub3d->camera.pos.z
	};
	spos[1] = (t_vec3d){
		wpos_b.x * cam_cos - wpos_b.y * cam_sin,
		wpos_b.y * cam_cos + wpos_b.x * cam_sin,
		-cub3d->camera.pos.z
	};
	float	cam_rot_x = cub3d->camera.rot.x;
	if (cam_rot_x > 180)
		cam_rot_x -= 360;
	spos[0].z -= cam_rot_x * spos[0].y / 32.;
	spos[1].z -= cam_rot_x * spos[1].y / 32.;

	//spos[0] = vec3d_rotate(spos[0], -cub3d->camera.rot.z * (M_PI / 180.0f), (t_vec3d){0, 0, 1});
	//spos[1] = vec3d_rotate(spos[1], -cub3d->camera.rot.z * (M_PI / 180.0f), (t_vec3d){0, 0, 1});

	spos[2] = spos[0];
	spos[2].z += 40; 
	spos[3] = spos[1];
	spos[3].z += 40; 
	
	spos[0] = to_screen(cub3d, spos[0]);
	spos[1] = to_screen(cub3d, spos[1]);
	spos[2] = to_screen(cub3d, spos[2]);
	spos[3] = to_screen(cub3d, spos[3]);

	//printf("Wall A: (%f, %f)\n", spos[0].x, spos[0].y);
	//printf("Wall B: (%f, %f)\n", spos[1].x, spos[1].y);

	if (spos[0].x > 0 && spos[0].x < cub3d->width && spos[0].y > 0 && spos[0].y < cub3d->height)
		put_pixel_color(cub3d->buffer, spos[0].x, spos[0].y, 0x00FF00);
	if (spos[1].x > 0 && spos[1].x < cub3d->width && spos[1].y > 0 && spos[1].y < cub3d->height)
		put_pixel_color(cub3d->buffer, spos[1].x, spos[1].y, 0xFF0000);
	if (spos[2].x > 0 && spos[2].x < cub3d->width && spos[2].y > 0 && spos[2].y < cub3d->height)
		put_pixel_color(cub3d->buffer, spos[2].x, spos[2].y, 0x00FF00);
	if (spos[3].x > 0 && spos[3].x < cub3d->width && spos[3].y > 0 && spos[3].y < cub3d->height)
		put_pixel_color(cub3d->buffer, spos[3].x, spos[3].y, 0x00FF00);

	draw_wall(cub3d, spos[0], spos[1], spos[2].y, spos[3].y);
}

void	tick_update(t_cub3d *cub3d)
{
	ft_bzero(cub3d->buffer.data, cub3d->buffer.size * sizeof(u_int));

	test_wall(cub3d, (t_vec3d){40, 10, 0}, (t_vec3d){90, 10, 0});
	test_wall(cub3d, (t_vec3d){40, 10, 0}, (t_vec3d){40, 60, 0});
	test_wall(cub3d, (t_vec3d){90, 10, 0}, (t_vec3d){90, 60, 0});

	if (get_key_state(cub3d, 'a') == KEY_DOWN)
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos,
			vec3d_scale(rot_right(cub3d->camera.rot), -80 * cub3d->delta_t));
	if (get_key_state(cub3d, 'd') == KEY_DOWN)
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos,
			vec3d_scale(rot_right(cub3d->camera.rot), 80 * cub3d->delta_t));
	if (get_key_state(cub3d, 'w') == KEY_DOWN)
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos,
			vec3d_scale(rot_forward(cub3d->camera.rot), 80 * cub3d->delta_t));
	if (get_key_state(cub3d, 's') == KEY_DOWN)
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos,
			vec3d_scale(rot_forward(cub3d->camera.rot), -80 * cub3d->delta_t));
	if (get_key_state(cub3d, 'q') == KEY_DOWN)
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos,
			vec3d_scale(rot_up(cub3d->camera.rot), 80 * cub3d->delta_t));
	if (get_key_state(cub3d, 'e') == KEY_DOWN)
		cub3d->camera.pos = vec3d_add(cub3d->camera.pos,
			vec3d_scale(rot_up(cub3d->camera.rot), -80 * cub3d->delta_t));

	if (get_key_state(cub3d, XK_Up) == KEY_DOWN)
		cub3d->camera.rot.x -= 80 * cub3d->delta_t;
	if (get_key_state(cub3d, XK_Down) == KEY_DOWN)
		cub3d->camera.rot.x += 80 * cub3d->delta_t;
	if (get_key_state(cub3d, XK_Left) == KEY_DOWN)
		cub3d->camera.rot.z -= 80 * cub3d->delta_t;
	if (get_key_state(cub3d, XK_Right) == KEY_DOWN)
		cub3d->camera.rot.z += 80 * cub3d->delta_t;
	
	if (cub3d->camera.rot.x > 359)
		cub3d->camera.rot.x -= 360;
	if (cub3d->camera.rot.x < 0)
		cub3d->camera.rot.x += 360;
	if (cub3d->camera.rot.z > 359)
		cub3d->camera.rot.z -= 360;
	if (cub3d->camera.rot.z < 0)
		cub3d->camera.rot.z += 360;	

	t_vec3d rot = cub3d->camera.rot;
	printf("Camera rot: (%f, %f, %f)\n", rot.x, rot.y, rot.z);
	//printf("Camera pos: (%f, %f, %f)\n", cub3d->camera.pos.x, cub3d->camera.pos.y, cub3d->camera.pos.z);
}