/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:54:11 by upopee            #+#    #+#             */
/*   Updated: 2017/06/08 18:00:12 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_simple_color(t_scene *world, int color)
{
	int		i;
	int		j;

	j = world->width;
	while (j--)
	{
		i = world->height;
		while (i--)
			world->map[i][j].color = ft_itorgba(color);
	}
}

void	apply_color_set(t_scene *wld, t_colors *set, int n)
{
	int			i;
	int			j;
	int			curr;
	t_vertex3f	*pt;

	curr = set->marked_color[n];
	set->slice_down = (set->marked_alt[n] - wld->alt_min) / (float)(curr + 1);
	set->slice_up = (wld->alt_max - set->marked_alt[n])
					/ (float)(set->nb_colors[n] - (curr + 1));
	j = wld->width;
	while (j--)
	{
		i = wld->height;
		while (i--)
		{
			curr = 1;
			pt = &(wld->map[i][j]);
			if (pt->y < set->marked_alt[n])
			{
				while (pt->y < curr * set->slice_down)
					curr++;
			}
			else
			{
				while (pt->y > curr * set->slice_up)
					curr++;
			}
			pt->color = ft_itorgba(set->colors[set->curr_set][curr]);
		}
	}
}
