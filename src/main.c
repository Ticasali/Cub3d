/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:12:22 by dderny            #+#    #+#             */
/*   Updated: 2025/05/11 14:10:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

void	put_pixel_color(u_int *img_data, int img_size, int x, int y, t_color color);
inline void	put_pixel_color(u_int *img_data, int img_size, int x, int y, t_color color)
{
	img_data[y * img_size + x] = color.rgb;
}

void	draw_line(t_img *img, t_vec3d p1, t_vec3d p2, t_color color)
{
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;
	double x = p1.x;
	double y = p1.y;

	for (int i = 0; i <= steps; i++)
	{
		if (x < 0 || x >= img->width || y < 0 || y >= img->height)
			break;
		put_pixel_color((u_int *)img->data, img->size_line / 4, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void draw_square(t_img *img, t_vec3d p1, t_vec3d p2, t_color color)
{
	int x = p1.x;
	int y = p1.y;
	int size_x = p2.x - p1.x;
	int size_y = p2.y - p1.y;

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if (x + i < 0 || x + i >= img->width || y + j < 0 || y + j >= img->height)
				continue;
			put_pixel_color((u_int *)img->data, img->size_line / 4, x + i, y + j, color);
		}
	}
}

typedef struct s_plane
{
	t_vec3d a;
	t_vec3d b;
	t_vec3d c;
	t_vec3d d;
}	t_plane;

static int is_point_in_plane(t_vec3d point, t_plane plane)
{
	t_vec3d crossabp = vec3d_cross(vec3d_sub(plane.b, plane.a), vec3d_sub(point, plane.a));
	t_vec3d crossbcp = vec3d_cross(vec3d_sub(plane.c, plane.b), vec3d_sub(point, plane.b));
	t_vec3d crosscdp = vec3d_cross(vec3d_sub(plane.d, plane.c), vec3d_sub(point, plane.c));
	t_vec3d crossdap = vec3d_cross(vec3d_sub(plane.a, plane.d), vec3d_sub(point, plane.d));
	if (vec3d_dot(crossabp, crossbcp) < 0)
		return (0);
	if (vec3d_dot(crossbcp, crosscdp) < 0)
		return (0);
	if (vec3d_dot(crosscdp, crossdap) < 0)
		return (0);
	if (vec3d_dot(crossdap, crossabp) < 0)
		return (0);
	return (1);
}

static int intersect_segment_plane(t_vec3d p1, t_vec3d p2, t_plane plane, t_vec3d *intersection)
{
	t_vec3d n = vec3d_cross(vec3d_sub(plane.b, plane.a), vec3d_sub(plane.c, plane.a));
	double d = vec3d_dot(n, plane.a);
	double t = (d - vec3d_dot(n, p1)) / vec3d_dot(n, vec3d_sub(p2, p1));
	if (t < 0 || t > 1)
		return (0);
	*intersection = vec3d_add(p1, vec3d_scale(vec3d_sub(p2, p1), t));
	return (is_point_in_plane(*intersection, plane));
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


t_color calculate_pixel_color(t_cub3d *cub3d, int x, int y, int *size)
{
	size_t i;
	t_color c;
	t_vec3d intersection;

	(void) y;
	c.rgb = 0x000000;
	t_vec3d pos = (t_vec3d){
		2 * x / (double)cub3d->width - 1,
		0,
		0
	};
	t_vec3d ray_dir = {
		camera_dir.x + camera_plane.x * pos.x,
		camera_dir.y + camera_plane.y * pos.x,
		0
	};
	ray_dir = vec3d_normalize(ray_dir);
	draw_line(cub3d->buffer, vec3d_add(camera_pos, (t_vec3d){200, 200, 0}), vec3d_add(vec3d_add(camera_pos, (t_vec3d){200, 200, 0}), vec3d_scale(ray_dir, 45)), (t_color){0x00FFFF});
	i = 0;
	while (i < 6)
	{
		if (intersect_segment_plane(camera_pos, vec3d_add(camera_pos,  vec3d_scale(ray_dir, 99999)), scene_planes[i], &intersection))
		{
			*size = cub3d->height / vec3d_dist(camera_pos, intersection) * 25;
			c.rgb = plane_colors[i];
			c.r *= ft_fclamp(1 - vec3d_dist(camera_pos, intersection) / 150, 0, 1);
			c.g *= ft_fclamp(1 - vec3d_dist(camera_pos, intersection) / 150, 0, 1);
			c.b *= ft_fclamp(1 - vec3d_dist(camera_pos, intersection) / 150, 0, 1);
			break;
		}
		i++;
	}
	return (c);
}

int key_hook(int keycode, t_cub3d *cub3d)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == 65307) // ESC key
	{
		mlx_destroy_window(cub3d->mlx, cub3d->win);
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
		exit(0);
	}
	if (keycode == 65363) // UP arrow key
	{
		camera_dir = vec3d_rotate(camera_dir, (12.f / 360.f), (t_vec3d){0, 0, 1});
		camera_plane = vec3d_rotate(camera_plane, (12.f / 360.f), (t_vec3d){0, 0, 1});
	}
	else if (keycode == 65361) // DOWN arrow key
	{
		camera_dir = vec3d_rotate(camera_dir, -(12.f / 360.f), (t_vec3d){0, 0, 1});
		camera_plane = vec3d_rotate(camera_plane, -(12.f / 360.f), (t_vec3d){0, 0, 1});
	}
	if (keycode == 'a') // LEFT arrow key
	{
		camera_pos.x += camera_dir.x * 2;
	}
	else if (keycode == 'd') // RIGHT arrow key
	{
		camera_pos.x -= camera_dir.x * 2;
	}
	if (keycode == 'w') // UP arrow key
	{
		camera_pos.y += camera_dir.y * 2;
	}
	else if (keycode == 's') // DOWN arrow key
	{
		camera_pos.y -= camera_dir.y * 2;
	}
	return (0);
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

	cub3d->buffer = mlx_new_image(cub3d->mlx, cub3d->width, cub3d->height);
	if (!cub3d->buffer)
	{
		perror("Error creating image");
		mlx_destroy_window(cub3d->mlx, cub3d->win);
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
		return (1);
	}
	u_int	*img_data = (u_int *)cub3d->buffer->data;
	int size_line = cub3d->buffer->size_line >> 2;


	int sizex = 400;
	int sizey = 400;
	// cam pos on mini map at top left corner
	draw_square(cub3d->buffer, (t_vec3d){0, 0, 0}, (t_vec3d){sizex, sizey, 0}, (t_color){0xFFFFFF});

	draw_square(cub3d->buffer, (t_vec3d){sizex / 2 - 5 + camera_pos.x, sizey / 2 - 5 + camera_pos.y, 0}, (t_vec3d){sizex / 2 + 5 + camera_pos.x, sizey / 2 + 5 + camera_pos.y, 0}, (t_color){0x00FF00});
	// draw camera direction
	draw_line(cub3d->buffer, (t_vec3d){sizex / 2 + camera_pos.x, sizey / 2 + camera_pos.y, 0}, (t_vec3d){sizex / 2 + camera_pos.x + camera_dir.x * 45, sizey / 2 + camera_pos.y + camera_dir.y * 45, 0}, (t_color){0xFF0000});
	// draw camera plane
	draw_line(cub3d->buffer, (t_vec3d){sizex / 2 + camera_pos.x, sizey / 2 + camera_pos.y, 0}, (t_vec3d){sizex / 2 + camera_pos.x + camera_plane.x * 45, sizey / 2 + camera_pos.y + camera_plane.y * 45, 0}, (t_color){0x00FF00});


	//while (y < cub3d->height)
	//{
		y = cub3d->height / 2;
		x = 0;
		int w = cub3d->width;
		while (x < w)
		{
			int size = 0;
			t_color color = calculate_pixel_color(cub3d, x, 0, &size);
			int i = ft_max(y - size / 2, 0) - 1;
			int max = ft_min(y + size / 2, cub3d->height);
			while (++i < max)
				put_pixel_color(img_data, size_line, x, i, color);
			x++;
		}
		//y++;
	//}

	int i = 0;
	t_vec3d pos = {sizex / 2, sizey / 2, 0};
	while (i < 6)
	{
		draw_line(cub3d->buffer, vec3d_add(pos, scene_planes[i].a), vec3d_add(pos, scene_planes[i].b), (t_color){plane_colors[i]});
		draw_line(cub3d->buffer, vec3d_add(pos, scene_planes[i].b), vec3d_add(pos, scene_planes[i].c), (t_color){plane_colors[i]});
		draw_line(cub3d->buffer, vec3d_add(pos, scene_planes[i].c), vec3d_add(pos, scene_planes[i].d), (t_color){plane_colors[i]});
		draw_line(cub3d->buffer, vec3d_add(pos, scene_planes[i].d), vec3d_add(pos, scene_planes[i].a), (t_color){plane_colors[i]});
		i++;
	}

	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer, 0, 0);
	mlx_destroy_image(cub3d->mlx, cub3d->buffer);
	return (0);
}

int	main(void)
{
	t_cub3d	cub3d;

	

	cub3d = (t_cub3d){0};
	cub3d.width = 1920;
	cub3d.height = 1080;
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
	mlx_hook(cub3d.win, 2, 1L << 0, key_hook, &cub3d);
	mlx_loop_hook(cub3d.mlx, &update, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
