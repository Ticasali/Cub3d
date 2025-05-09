/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:12:22 by dderny            #+#    #+#             */
/*   Updated: 2025/05/09 03:43:31 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "color.h"
#include "vec3d.h"
#include <math.h>
#include <mlx.h>
#include <mlx_int.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

void	put_pixel_color(t_img *img, int x, int y, t_color color)
{
	*(u_int *)(img->data + (y * img->size_line + x * 4)) = color.rgb;
}

typedef struct s_plane
{
	t_vec3d a;
	t_vec3d b;
	t_vec3d c;
	t_vec3d d;
}	t_plane;

static int is_point_in_polygon(t_vec3d point, t_plane plane)
{
	t_vec3d ab = vec3d_sub(plane.b, plane.a);
	t_vec3d ac = vec3d_sub(plane.c, plane.a);
	t_vec3d ap = vec3d_sub(point, plane.a);
	double d1 = vec3d_dot(ab, ac);
	double d2 = vec3d_dot(ac, ap);
	double d3 = vec3d_dot(ab, ap);
	if (d1 * d2 < 0 || d1 * d3 < 0)
		return (0);
	return (1);
}

static int intersect_segment_plane(t_vec3d p1, t_vec3d p2, t_plane plane)
{
	t_vec3d n = vec3d_cross(vec3d_sub(plane.b, plane.a), vec3d_sub(plane.c, plane.a));
	double d = vec3d_dot(n, plane.a);
	double t = (d - vec3d_dot(n, p1)) / vec3d_dot(n, vec3d_sub(p2, p1));
	if (t < 0 || t > 1)
		return (0);
	t_vec3d intersection = vec3d_add(p1, vec3d_scale(vec3d_sub(p2, p1), t));
	return (is_point_in_polygon(intersection, plane));
}

int plane_colors[6] = {
	0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF
};
t_plane scene_planes[6];
double fov = 90;
t_vec3d camera_pos = {0, 0, 0};
t_vec3d camera_dir = {-1, 0, 0};
t_vec3d camera_plane = {0, 0.66, 0};

double aspect_ratio = 16.0 / 9.0;


t_color calculate_pixel_color(t_cub3d *cub3d, int x, int y)
{
	size_t i;
	t_color c;

	c.rgb = 0x000000;
	i = 0;
	while (i < 6)
	{
		camera_pos = (t_vec3d){
			2 * x / (double)cub3d->width - 1,
			1 - 2 * y / (double)cub3d->height,
			0
		};
		t_vec3d ray_dir = {
			camera_dir.x + camera_plane.x * camera_pos.x,
			camera_dir.y + camera_plane.y * camera_pos.x,
			camera_dir.z + camera_plane.z * camera_pos.x
		};
		if (intersect_segment_plane(camera_pos, ray_dir, scene_planes[i]))
		{
			c.rgb = plane_colors[i];
			break;
		}
		i++;
	}
	return (c);
}

int update(t_cub3d *cub3d)
{
	static struct timeval current_time = {0};
	static struct timeval last_time;
	double delta_time;
	int x = 0;
	int y = 0;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec == last_time.tv_sec && current_time.tv_usec == last_time.tv_usec)
		return (0);
	delta_time = (current_time.tv_sec - last_time.tv_sec) * 1000.0 + (current_time.tv_usec - last_time.tv_usec) / 1000.0;
	printf("FPS: %ld\n", (long)(1000 / delta_time));
	last_time.tv_sec = current_time.tv_sec;
	last_time.tv_usec = current_time.tv_usec;

	// rotate camera 360 degrees clockwise
	camera_dir.x = cos(delta_time / 1000) * camera_dir.x - sin(delta_time / 1000) * camera_dir.y;
	camera_dir.y = sin(delta_time / 1000) * camera_dir.x + cos(delta_time / 1000) * camera_dir.y;
	camera_plane.x = -camera_dir.y * aspect_ratio;
	camera_plane.y = camera_dir.x * aspect_ratio;
	camera_plane.z = 0;

	while (y < cub3d->height)
	{
		x = 0;
		while (x < cub3d->width)
		{
			put_pixel_color(cub3d->buffer, x, y, calculate_pixel_color(cub3d, x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer, 0, 0);
	return (0);
}

int	main(void)
{
	t_cub3d	cub3d;

	double size = 0.1;
	scene_planes[0] = (t_plane){(t_vec3d){-size, -size, 0}, (t_vec3d){size, -size, 0}, (t_vec3d){size, size, 0}, (t_vec3d){-size, size, 0}};
	scene_planes[1] = (t_plane){(t_vec3d){-size, -size, 0}, (t_vec3d){-size, size, 0}, (t_vec3d){-size, size, -size}, (t_vec3d){-size, -size, -size}};
	scene_planes[2] = (t_plane){(t_vec3d){size, -size, 0}, (t_vec3d){size, size, 0}, (t_vec3d){size, size, -size}, (t_vec3d){size, -size, -size}};
	scene_planes[3] = (t_plane){(t_vec3d){-size, -size, -size}, (t_vec3d){size, -size, -size}, (t_vec3d){size, size, -size}, (t_vec3d){-size, size, -size}};
	scene_planes[4] = (t_plane){(t_vec3d){-size, -size, 0}, (t_vec3d){-size, -size, -size}, (t_vec3d){size, -size, -size}, (t_vec3d){size, -size, 0}};
	scene_planes[5] = (t_plane){(t_vec3d){-size, size, 0}, (t_vec3d){-size, size, -size}, (t_vec3d){size, size, -size}, (t_vec3d){size, size, 0}};

	camera_dir.x = cos(fov * M_PI / 180);
	camera_dir.y = sin(fov * M_PI / 180);
	camera_plane.x = -camera_dir.y * aspect_ratio;
	camera_plane.y = camera_dir.x * aspect_ratio;
	camera_plane.z = 0;

	cub3d = (t_cub3d){0};
	cub3d.width = 1920 / 2;
	cub3d.height = 1080 / 2;
	cub3d.mlx = mlx_init();
	if (!cub3d.mlx)
	{
		perror("Error initializing mlx");
		return (1);
	}
	cub3d.win = mlx_new_window(cub3d.mlx, cub3d.width, cub3d.height, "Cub3D");
	if (!cub3d.win)
	{
		perror("Error creating window");
		mlx_destroy_display(cub3d.mlx);
		free(cub3d.mlx);
		return (1);
	}
	cub3d.buffer = mlx_new_image(cub3d.mlx, cub3d.width, cub3d.height);
	if (!cub3d.buffer)
	{
		perror("Error creating image");
		mlx_destroy_window(cub3d.mlx, cub3d.win);
		mlx_destroy_display(cub3d.mlx);
		free(cub3d.mlx);
		return (1);
	}
	mlx_loop_hook(cub3d.mlx, &update, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
