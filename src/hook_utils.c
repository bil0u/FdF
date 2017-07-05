/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:34:14 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 19:48:24 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "color_utils.h"

void		zoom(t_mod *mod, float zoom_value)
{
	t_mod	m;

	m = *mod;
	if ((m.zoom * zoom_value) <= MIN_ZOOM
		&& (m.zoom * zoom_value) >= MAX_ZOOM)
		m.zoom *= zoom_value;
	*mod = m;
}

void		next_proj(t_mod *mod)
{
	t_mod	m;

	m = *mod;
	m.proj_type = (m.proj_type + 1) % NB_PROJS;
	m.scale = ft_to_vec3(DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
	if (m.proj_type == ORTHOGRAPHIC_PROJ)
		m.scale = ft_vec3_scale(m.scale, 0.01);
	m.keymod &= OFF(NEXT_PROJ);
	*mod = m;
}

void		next_color(t_scene *w, t_colors *c, int *keys)
{
	int		i;
	int		k;

	i = c->curr_set;
	k = *keys;
	if (FULL_SET_SET(k))
	{
		c->curr_set = (i + 1) % NB_COLORSETS;
		apply_color_set(w, *c);
	}
	else
	{
		c->curr_color[i] = (c->curr_color[i] + 1) % c->nb_colors[i];
		apply_simple_color(w, c->colors[i][c->curr_color[i]]);
	}
	k &= OFF(NEXT_COLOR);
	*keys = k;
}
