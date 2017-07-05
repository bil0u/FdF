/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 17:44:08 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "color_utils.h"

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
	get_alt_range(world);
}

void			center_scene(t_scene *world)
{
	t_vector3	center;

	get_alt_range(world);
	if (world->alt_range > 50.0)
		reduce_alt(world);
	center.x = (float)(world->width - 1) * 0.5;
	center.y = world->alt_min > 0.0 ? world->alt_min : -(world->alt_min);
	center.z = (float)(world->height - 1) * 0.5;
	world->center_matrix = ft_gen_translate_mat4(ft_vec3_opp(center));
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
