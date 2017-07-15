/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:54:11 by upopee            #+#    #+#             */
/*   Updated: 2017/07/10 04:00:51 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void			apply_simple_color(t_scene *world, int color)
{
	int		i;
	int		j;

	j = world->width;
	while (j--)
	{
		i = world->height;
		while (i--)
			world->map[i][j].color = color;
	}
}


static int		color_from_set(t_colors set, int alt, float amin, float amax)
{
	int			color_index;
	t_frange	in;
	t_frange	out;

	if (alt >= set.marked_alt[set.curr_set])
	{
		in.min = set.marked_alt[set.curr_set];
		in.max = amax;
		out.min = set.marked_colorup[set.curr_set];
		out.max = set.nb_colors[set.curr_set] - 1;
	}
	else
	{
		in.min = amin;
		in.max = set.marked_alt[set.curr_set];
		out.min = 0.0;
		out.max = set.marked_colorup[set.curr_set] - 1.0;
		out.max = out.max <= 0.0 ? 0.0 : out.max;
	}
	color_index = ft_to_frange(in, out, (float)alt);
	return (set.colors[set.curr_set][(int)color_index]);
}

void			apply_color_set(t_scene *world, t_colors set)
{
	int			i;
	int			j;

	j = world->width;
	while (j--)
	{
		i = world->height;
		while (i--)
			world->map[i][j].color = color_from_set(set, world->map[i][j].y,
												world->alt_min, world->alt_max);
	}
}
