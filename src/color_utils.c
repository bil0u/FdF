/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:54:11 by upopee            #+#    #+#             */
/*   Updated: 2017/07/16 03:08:05 by upopee           ###   ########.fr       */
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

static int		color_shade(t_colorset s, float c, int nb_colors)
{
	int		c1;
	int		c2;

	c1 = s[(int)c];
	c2 = (((int)c >= (nb_colors - 1)) ? s[(int)c] : s[(int)c + 1]);
	return (ft_icolor_lerp(c1, c2, (c - floorf(c))));
}

static int		color_from_set(t_colors set, int alt, float amin, float amax)
{
	float		c;
	int			i;
	t_frange	in;
	t_frange	out;

	i = set.curr_set;
	if (alt >= set.marked_alt[i])
	{
		in.min = set.marked_alt[i];
		in.max = amax;
		out.min = set.marked_colorup[i];
		out.max = set.nb_colors[i] - 1;
	}
	else
	{
		in.min = amin;
		in.max = set.marked_alt[i];
		out.min = 0.0;
		out.max = set.marked_colorup[i] - 1.0;
		out.max = out.max <= 0.0 ? 0.0 : out.max;
	}
	c = ft_to_frange(in, out, (float)alt);
	return (color_shade(set.colors[i], c, set.nb_colors[i]));
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
