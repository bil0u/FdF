/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/26 17:47:55 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void		get_alt_range(t_scene *world)
{
	t_vector3	curr;
	float		min;
	float		max;
	int			i;
	int			j;

	min = (world->map[0][0]).y;
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

void			center_scene(t_scene *world)
{
	t_vector3	center;
	t_vector3	*curr;
	int			i;
	int			j;

	get_alt_range(world);
	center.x = (float)(world->width - 1) * 0.5;
	center.y = world->alt_range == 0 ? world->alt_min : world->alt_range * 0.5;
	center.z = (float)(world->height - 1) * 0.5;
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			curr = world->map[i] + j;
			curr->x -= center.x;
			curr->y -= center.y;
			curr->z -= center.z;
		}
	}
}

void			get_cam_pos(t_scene *world)
{
	float	width;
	float	height;

	width = (float)world->width;
	height = (float)world->height;
	world->mod.cam_eye.z = MAX(height, width) * DEFAULT_SCALE_Z * 0.75;
	world->mod.cam_eye.x = MIN(height, width) * DEFAULT_SCALE_X * 0.75;
	world->mod.cam_eye.y = MAX(height, width) * DEFAULT_SCALE_Y * 0.5;
	world->mod.cam_to.x = 0.0;
	world->mod.cam_to.y = 0.0;
	world->mod.cam_to.z = 0.0;
	world->mod.cam_upv.x = 0.0;
	world->mod.cam_upv.y = 1.0;
	world->mod.cam_upv.z = 0.0;
}

void			reset_modifiers(t_scene *world)
{
	world->mod.translate.x = 0.0;
	world->mod.translate.y = 0.0;
	world->mod.translate.z = 0.0;
	world->mod.scale.x = DEFAULT_SCALE_X;
	world->mod.scale.y = DEFAULT_SCALE_Y;
	world->mod.scale.z = DEFAULT_SCALE_Z;
	world->mod.rot_axis.x = 0.0;
	world->mod.rot_axis.y = 1.0;
	world->mod.rot_axis.z = 0.0;
	world->mod.rot_angle = DEFAULT_ROT_ANGLE;
}
