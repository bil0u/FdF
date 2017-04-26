/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/27 00:41:11 by upopee           ###   ########.fr       */
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
	world->mod.cam_eye.z = -(MAX(height, width) * DEFAULT_SCALE_Z * 0.8);
	world->mod.cam_eye.x = 0.0;
	world->mod.cam_eye.y = MAX(height, width) * DEFAULT_SCALE_Y * 0.6;
	world->mod.cam_to = ft_to_vec3(0.0, 0.0, 0.0);
	world->mod.cam_upv = ft_to_vec3(0.0, 1.0, 0.0);
}

void			reset_modifiers(t_scene *world)
{
	world->mod.translate = ft_to_vec3(0.0, 0.0, 0.0);
	world->mod.scale = ft_to_vec3(DEFAULT_SCALE_X,
									DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
	world->mod.rot_axis = ft_to_vec3(0.0, 1.0, 0.0);
	world->mod.rot_angle = DEFAULT_ROT_ANGLE;
}
