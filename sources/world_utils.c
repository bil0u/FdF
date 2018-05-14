/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2018/05/14 02:08:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "color_utils.h"

void		get_alt_range(t_scene *world)
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

float		alt_reducer(float alt_range)
{
	float	factor;

	if (alt_range > ALT_EXTREME)
		factor = REDUCE_FACTOR_EXTREME;
	else if (alt_range > ALT_VERYHIGH)
		factor = REDUCE_FACTOR_VERYHIGH;
	else if (alt_range > ALT_HIGH)
		factor = REDUCE_FACTOR_HIGH;
	else if (alt_range > ALT_MID)
		factor = REDUCE_FACTOR_MID;
	else if (alt_range > ALT_LOW)
		factor = REDUCE_FACTOR_LOW;
	else
		factor = REDUCE_FACTOR_VERYLOW;
	return (factor);
}

void		center_scene(t_scene *world)
{
	t_vector3	center;

	center.x = (float)(world->width - 1) * 0.5;
	if (world->alt_min <= 0.0 && world->alt_max > 0.0)
		center.y = 0.0;
	else
		center.y = world->alt_min + (world->alt_range * 0.5);
	center.z = (float)(world->height - 1) * 0.5;
	world->center_matrix = ft_gen_translate_mat4(ft_vec3_opp(center));
}

void		get_cam_pos(t_scene *world)
{
	float	width;
	float	height;
	t_mod	m;

	m = world->mod;
	width = (float)world->width;
	height = (float)world->height;
	m.cam_eye.z = MAX(height, width) * 1.0;
	m.cam_eye.x = 0.0;
	m.cam_eye.y = MAX(height, width) * 0.6;
	m.cam_to = ft_to_vec3(0.0, 0.0, 0.0);
	m.cam_upv = ft_to_vec3(0.0, 1.0, 0.0);
	world->mod = m;
}
