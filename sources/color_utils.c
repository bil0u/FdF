/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:54:11 by upopee            #+#    #+#             */
/*   Updated: 2017/07/26 22:50:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static int		color_from_mset(t_colors set, int alt, float amin, float amax)
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
	alt = (int)c == set.nb_colors[i] - 1 ? (int)c : (int)c + 1;
	return (ft_icolor_lerp(set.colors[i][(int)c], set.colors[i][alt],
																c - floorf(c)));
}

static int		color_from_fset(t_colors set, int alt, float amin, float amax)
{
	float		c;
	int			i;
	t_frange	in;
	t_frange	out;

	i = set.curr_set;
	if (amin == amax)
		return (set.colors[i][0]);
	in.min = amin;
	in.max = amax;
	out.min = 0.0;
	out.max = set.nb_colors[i] - 1;
	c = ft_to_frange(in, out, (float)alt);
	alt = (int)c == set.nb_colors[i] - 1 ? (int)c : (int)c + 1;
	return (ft_icolor_lerp(set.colors[i][(int)c], set.colors[i][alt],
																c - floorf(c)));
}

void			apply_markedset(t_scene *world, t_colors set)
{
	int			i;
	int			j;

	j = world->width;
	while (j--)
	{
		i = world->height;
		while (i--)
			world->map[i][j].color = color_from_mset(set, world->map[i][j].y,
												world->alt_min, world->alt_max);
	}
}

void			apply_colorset(t_scene *world, t_colors set)
{
	int			i;
	int			j;

	j = world->width;
	while (j--)
	{
		i = world->height;
		while (i--)
			world->map[i][j].color = color_from_fset(set, world->map[i][j].y,
												world->alt_min, world->alt_max);
	}
}

void			apply_color(t_scene *world, int color)
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
