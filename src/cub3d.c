/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 03:23:26 by dderny            #+#    #+#             */
/*   Updated: 2025/05/12 13:14:46 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mlx.h"

static void	time_update(t_cub3d *cub3d)
{
	struct timeval tv;
	static double lasttime = 0;
	double time;

	gettimeofday(&tv, NULL)	;
	time = (tv.tv_sec * 1000 + (double)tv.tv_usec / 1000) / 1000.0;
	if (!lasttime)
		lasttime = time;
	cub3d->time = time;
	cub3d->delta_t = time - lasttime;
	lasttime = time;
	
	printf("Time: %f, FPS: %d\n", cub3d->delta_t, (int)(1 / cub3d->delta_t));
}

int	update(t_cub3d *cub3d)
{
	int i;
	
	time_update(cub3d);
	tick_update(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer.img, 0, 0);
	i = -1;
	while (++i < cub3d->key_downs)
	{
		if (!cub3d->keys[i][0])
			continue ;
		if (cub3d->keys[i][1] == KEY_PRESSED)
			cub3d->keys[i][1] = KEY_DOWN;
		if (cub3d->keys[i][1] == KEY_RELEASED)
		{
			cub3d->key_downs--;
			cub3d->keys[i][0] = 0;
		}
	}
	return (0);
}

int on_destroy(t_cub3d *cub3d)
{
	mlx_do_key_autorepeaton(cub3d->mlx);
	if (cub3d->buffer.img)
		mlx_destroy_image(cub3d->mlx, cub3d->buffer.img);
	if (cub3d->win)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	if (cub3d->mlx)
	{
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
	}
	exit(0);
	return (0);
}

int on_keypressed(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
		on_destroy(cub3d);
	cub3d->keys[cub3d->key_downs][0] = keycode;
	cub3d->keys[cub3d->key_downs][1] = KEY_PRESSED;
	cub3d->key_downs++;
	return (0);
}

int on_keyreleased(int keycode, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->key_downs)
	{
		if (cub3d->keys[i][0] == keycode)
		{
			cub3d->keys[i][1] = KEY_RELEASED;
			break ;
		}
		i++;
	}
	return (0);
}

int	get_key_state(t_cub3d *cub3d, int keycode)
{
	int	i;

	i = 0;
	while (i < cub3d->key_downs)
	{
		if (cub3d->keys[i][0] == keycode)
			return (cub3d->keys[i][1]);
		i++;
	}
	return (0);
}

void	init_window(t_cub3d *cub)
{
	cub->win = mlx_new_window(cub->mlx, cub->width, cub->height, "cub");
	if (!cub->win)
	{
		perror("Error creating window");
		mlx_destroy_display(cub->mlx);
		exit(1);
	}
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_hook(cub->win, KeyPress, KeyPressMask, &on_keypressed, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, &on_keyreleased, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask, &on_destroy, cub);
	cub->buffer.img = mlx_new_image(cub->mlx, cub->width, cub->height);
	if (!cub->buffer.img)
	{
		perror("Error creating image");
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		exit(1);
	}
	cub->buffer.data = (u_int *)mlx_get_data_addr(cub->buffer.img, &cub->buffer.size_line, &cub->buffer.size_line, &cub->buffer.height);
	cub->buffer.size_line /= 4;
	cub->buffer.width = cub->width;
	cub->buffer.height = cub->height;
	cub->buffer.size = cub->buffer.size_line * cub->buffer.height;
}

static void init_scene(t_cub3d *cub3d)
{
	cub3d->camera.pos = (t_vec3d){0, 0, 0};
	cub3d->camera.dir = (t_vec3d){0, 1, 0};
	cub3d->camera.plane = (t_vec3d){0.33, 0, 0};
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
	init_window(&cub3d);
	init_scene(&cub3d);
	mlx_loop_hook(cub3d.mlx, &update, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
