/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:25 by dderny            #+#    #+#             */
/*   Updated: 2025/05/24 06:20:44 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "draw.h"
# include "rotation.h"
# include "vec3d.h"

typedef struct s_plane
{
	t_vec3d a;
	t_vec3d b;
	t_vec3d c;
	t_vec3d d;
}	t_plane;

typedef struct  s_camera
{
	t_vec3d		pos;
	t_rot		rot;
}				t_camera;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_oimg		buffer;
	int			width;
	int			height;
	double		time;
	double		delta_t;
	int			keys[16][2];
	int			key_downs;
	t_camera	camera;
	float		cos[360];
	float		sin[360];
}	t_cub3d;

typedef enum
{
	KEY_PRESSED,
	KEY_DOWN,
	KEY_RELEASED
}	t_key_state;

void	tick_update(t_cub3d *cub3d);

int is_point_in_plane(t_vec3d point, t_plane plane);
int intersect_segment_plane(t_vec3d p1, t_vec3d p2, t_plane plane, t_vec3d *intersection);

int	get_key_state(t_cub3d *cub3d, int keycode);

#endif
