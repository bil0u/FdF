/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/30 19:01:14 by upopee           ###   ########.fr       */
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
	t_vector3	*curr;
	float		x_mid;
	float		z_mid;
	int			i;
	int			j;

	get_alt_range(world);
	x_mid = (float)(world->width - 1) * 0.5;
	z_mid = (float)(world->height - 1) * 0.5;
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			curr = world->map[i] + j;
			curr->x -= x_mid;
			curr->z -= z_mid;
		}
	}
}

void			get_cam_pos(t_scene *world)
{
	float	width;
	float	height;

	width = (float)world->width;
	height = (float)world->height;
	world->mod.cam_eye.z = MAX(height, width) * 0.5;
	world->mod.cam_eye.x = 0.0;
	world->mod.cam_eye.y = MAX(height, width) * 0.5;
	world->mod.cam_to = ft_to_vec3(0.0, 0.0, 0.0);
	world->mod.cam_upv = ft_to_vec3(0.0, 1.0, 0.0);
}

void			reset_modifiers(t_scene *world)
{
	get_cam_pos(world);
	world->mod.rot_bool = TRUE;
	world->mod.zoom_bool = TRUE;
	world->mod.rot_angle = DEFAULT_ROT_ANGLE;
	world->mod.rot_axis = ft_to_vec3(0.0, 1.0, 0.0);
	world->mod.zoom = DEFAULT_ZOOM;
	world->mod.translate = ft_to_vec3(0.0, 0.0, 0.0);
	world->mod.scale = ft_to_vec3(DEFAULT_SCALE_X,
									DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
}
