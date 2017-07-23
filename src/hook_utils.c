/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:34:14 by upopee            #+#    #+#             */
/*   Updated: 2017/07/19 15:43:25 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "color_utils.h"
#include "env_utils.h"
#include "world_utils.h"

void			zoom(t_mod *mod, float zoom_value)
{
	t_mod	m;
	m = *mod;
	if ((m.zoom + zoom_value) <= MIN_ZOOM
		&& (m.zoom + zoom_value) >= MAX_ZOOM)
		m.zoom += zoom_value;
	*mod = m;
}

void			next_proj(t_scene *wld, t_mod *mod)
{
	t_mod	m;

	m = *mod;
	m.proj_type = (m.proj_type + 1) % NB_PROJS;
	m.scale = ft_to_vec3(DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
	m.scale.y *= alt_reducer(wld->alt_range);
	if (m.proj_type == ORTHOGRAPHIC_PROJ)
		m.scale = ft_vec3_scale(m.scale, 0.008);
	m.keymod &= OFF(NEXT_PROJ);
	*mod = m;
}

void			col_tool(char f, t_scene *w, t_colors *c, int *keymod)
{
	int		i;
	int		k;

	i = c->curr_set;
	k = *keymod;
	if (f == 0)
	{
		FULL_SET_SET(k) ? (c->curr_set = (i + 1) % NB_COLORSETS)
				: (c->curr_color[i] = (c->curr_color[i] + 1) % c->nb_colors[i]);
		k &= OFF(NEXT_COLOR);
	}
	else if (f == 1)
	{
		if (FULL_SET_SET(k))
		 	MARKED_SET_SET(k) ? apply_markedset(w, *c) : apply_colorset(w, *c);
		else
			apply_color(w, c->colors[i][c->curr_color[i]]);
		k &= OFF(APPLY_COLORS);
	}
	*keymod = k;
}

static void		apply_actions(int k, t_mod *mod, float n)
{
	t_mod	m;
	float	z;

	m = *mod;
	z = Z_SPEED;
	SPEED_UP_SET(k) ? (z = Z_FAST) : (void)k;
	SPEED_DOWN_SET(k) ? (z = Z_SLOW) : (void)k;
	if (PLUS_SET(k))
		ZOOM_SET(k) ? zoom(&m, -(z)) : (m.scale.y += ALT_MOD_SPEED * n);
	if (MINUS_SET(k))
		ZOOM_SET(k) ? zoom(&m, z) : (m.scale.y -= ALT_MOD_SPEED * n);
	if (UP_SET(k))
		ROTATE_SET(k) ? (m.rot_x += R_SPEED * n) : (m.trans.z += T_SPEED * n);
	if (DOWN_SET(k))
		ROTATE_SET(k) ? (m.rot_x -= R_SPEED * n) : (m.trans.z -= T_SPEED * n);
	if (LEFT_SET(k))
		ROTATE_SET(k) ? (m.rot_y += R_SPEED * n) : (m.trans.x += T_SPEED * n);
	if (RIGHT_SET(k))
		ROTATE_SET(k) ? (m.rot_y -= R_SPEED * n) : (m.trans.x -= T_SPEED * n);
	*mod = m;
}

void			apply_mods(t_env *e, t_scene *w, t_mod *m)
{
	int			k;
	int			curr_set;
	t_colors	*c;
	float		n;

	c = &m->col;
	curr_set = c->curr_set;
	k = m->keymod;
	n = 1.0;
	SPEED_UP_SET(k) ? (n *= SPEED_UP_FACTOR) : (void)k;
	SPEED_DOWN_SET(k) ? (n *= SPEED_DOWN_FACTOR) : (void)k;
	QUIT_SET(k) ? end_session(e, NULL, EXIT_SUCCESS) : (void)k;
	RESET_SET(k) ? reset_modifiers(w) : (void)k;
	NEXT_PROJ_SET(k) ? next_proj(w, m) : (void)k;
	UNFORCE_COLOR_SET(k) ? m->force_c = 0 : (void)k;
	NEXT_COLOR_SET(k) && !m->force_c ? col_tool(0, w, c, &m->keymod) : (void)k;
	MARKED_UP_SET(k) ? (c->marked_alt[curr_set] += ALT_FACTOR * n) : (void)k;
	MARKED_LOW_SET(k) ? (c->marked_alt[curr_set] -= ALT_FACTOR * n) : (void)k;
	APPLY_COLORS_SET(k) && !m->force_c ? col_tool(1, w, c, &m->keymod) : (void)k;
	apply_actions(k, m, n);
}
