/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:34:14 by upopee            #+#    #+#             */
/*   Updated: 2017/07/09 22:29:58 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "color_utils.h"
#include "env_utils.h"

void			zoom(t_mod *mod, float zoom_value)
{
	t_mod	m;

	m = *mod;
	if ((m.zoom * zoom_value) <= MIN_ZOOM
		&& (m.zoom * zoom_value) >= MAX_ZOOM)
		m.zoom *= zoom_value;
	*mod = m;
}

void			next_proj(t_mod *mod)
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

void			next_color(t_scene *w, t_colors *c, int *keys)
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

static void		apply_actions(int k, t_mod *mod)
{
	t_mod	m;

	m = *mod;
	if (PLUS_SET(k))
		ZOOM_SET(k) ? zoom(&m, Z_PSPEED) : (m.scale.y += ALT_FACTOR);
	if (MINUS_SET(k))
		ZOOM_SET(k) ? zoom(&m, Z_MSPEED) : (m.scale.y -= ALT_FACTOR);
	if (UP_SET(k))
		ROTATE_SET(k) ? (m.rot_x += R_SPEED) : (m.translate.z += T_SPEED);
	if (DOWN_SET(k))
		ROTATE_SET(k) ? (m.rot_x -= R_SPEED) : (m.translate.z -= T_SPEED);
	if (LEFT_SET(k))
		ROTATE_SET(k) ? (m.rot_y += R_SPEED) : (m.translate.x += T_SPEED);
	if (RIGHT_SET(k))
		ROTATE_SET(k) ? (m.rot_y -= R_SPEED) : (m.translate.x -= T_SPEED);
	*mod = m;
}

void			apply_mods(t_env *e, t_scene *w, t_mod *m)
{
	int			k;
	int			curr_set;
	t_colors	*c;

	c = &m->col;
	curr_set = c->curr_set;
	k = m->keymod;
	QUIT_SET(k) ? end_session(e, NULL, EXIT_SUCCESS) : (void)k;
	RESET_SET(k) ? reset_modifiers(w) : (void)k;
	NEXT_PROJ_SET(k) ? next_proj(m) : (void)k;
	NEXT_COLOR_SET(k) && !m->force_c ? next_color(w, c, &m->keymod) : (void)k;
	MARKED_UP_SET(k) ? (c->marked_alt[curr_set] += ALT_FACTOR) : (void)k;
	MARKED_LOW_SET(k) ? (c->marked_alt[curr_set] -= ALT_FACTOR) : (void)k;
	if ((MARKED_UP_SET(k) || MARKED_LOW_SET(k)) && FULL_SET_SET(k))
		apply_color_set(w, *c);
	UNFORCE_COLOR_SET(k) ? m->force_c = 0 : (void)k;
	apply_actions(k, m);
}
