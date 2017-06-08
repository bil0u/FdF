/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/06/07 02:57:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void		get_alt_range(t_scene *world)
{
	t_vertex3f	curr;
	float		min;
	float		max;
	int			i;
	int			j;

	min = world->map[0][0].y;
	max = min;
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			curr = world->map[i][j];
			min = MIN(curr.y, min);
			max = MAX(curr.y, max);
		}
	}
	world->alt_min = min;
	world->alt_max = max;
	world->alt_range = max - min;
}

void			reduce_alt(t_scene *world)
{
	int			i;
	int			j;

	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
			world->map[i][j].y *= REDUCE_FACTOR;
	}
}

void			center_scene(t_scene *world)
{
	float		x_mid;
	float		y_mid;
	float		z_mid;
	int			i;
	int			j;

	get_alt_range(world);
	x_mid = (float)(world->width - 1) * 0.5;
	y_mid = world->alt_min > 0.0 ? world->alt_min : -(world->alt_min);
	z_mid = (float)(world->height - 1) * 0.5;
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			world->map[i][j].x -= x_mid;
			world->map[i][j].y -= y_mid;
			world->map[i][j].z -= z_mid;
		}
	}
	if (world->alt_range > 50.0)
		reduce_alt(world);
}

void			get_cam_pos(t_scene *world)
{
	float	width;
	float	height;

	width = (float)world->width;
	height = (float)world->height;
	world->mod.cam_eye.z = MAX(height, width) * 1.0;
	world->mod.cam_eye.x = 0.0;
	world->mod.cam_eye.y = MAX(height, width) * 0.6;
	world->mod.cam_to = ft_to_vec3(0.0, 0.0, 0.0);
	world->mod.cam_upv = ft_to_vec3(0.0, 1.0, 0.0);
}

void			reset_modifiers(t_scene *world)
{
	get_cam_pos(world);
	world->mod.rot_bool = TRUE;
	world->mod.zoom_bool = TRUE;
	world->mod.points_only = FALSE;
	world->mod.col.full_set = TRUE;
	world->mod.col.curr_set = 0;
	world->mod.col.curr_color = 0;
	world->mod.proj_type = PERSPECTIVE_PROJ;
	world->mod.rot_x = DEFAULT_ROT_X;
	world->mod.rot_y = DEFAULT_ROT_Y;
	world->mod.rot_z = DEFAULT_ROT_Z;
	world->mod.zoom = DEFAULT_ZOOM;
	world->mod.translate = ft_to_vec3(0.0, 0.0, 0.0);
	world->mod.scale = ft_to_vec3(DEFAULT_SCALE_X,
									DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
}
