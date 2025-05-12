/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:43:18 by dderny            #+#    #+#             */
/*   Updated: 2025/05/11 14:45:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "vec3d.h"
# include <sys/types.h>

typedef union u_color
{
	unsigned int	rgb;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
}			t_color;

typedef struct s_oimg
{
	void	*img;
	u_int	*data;
	int		size_line;
	int		width;
	int		height;
	int		size;
} t_oimg;

inline void put_pixel_color(const t_oimg img, const int x, const int y, u_int color);
void draw_line(const t_oimg img, const t_vec3d p1, const t_vec3d p2, const u_int color);
void draw_square(const t_oimg img, const t_vec3d p1, const t_vec3d p2, const u_int color);

#endif