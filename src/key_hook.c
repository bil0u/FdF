/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 20:55:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "help_utils.h"
#include "debug_utils.h"
#include "hook_utils.h"
#include "keyboard_fr.h"
#include "refresh_window.h"

int		key_press(int key, int *keymod)
{
	int		k;

	k = *keymod;
	(key == KEY_ESC || key == KEY_Q) ? k |= QUIT : (void)key;
	key == KEY_DEL ? k |= RESET : (void)key;
	key == KEY_R ? k |= ROTATE : (void)key;
	key == KEY_T ? k &= OFF(ROTATE) : (void)key;
	key == KEY_Z ? k |= ZOOM : (void)key;
	key == KEY_A ? k &= OFF(ZOOM) : (void)key;
	(key == KEY_ALT_LEFT || key == KEY_ALT_RIGHT) ? k ^= PTS_ONLY : (void)key;
	key == KEY_P ? k |= NEXT_PROJ : (void)key;
	key == KEY_SPACE ? k |= NEXT_COLOR : (void)key;
	key == KEY_C ? k ^= FULL_SET : (void)key;
	key == KEY_X ? k |= MARKED_UP : (void)key;
	key == KEY_V ? k |= MARKED_LOW : (void)key;
	key == KEY_PLUS ? k |= PLUS : (void)key;
	key == KEY_MINUS ? k |= MINUS : (void)key;
	key == KEY_UP ? k |= UP : (void)key;
	key == KEY_DOWN ? k |= DOWN : (void)key;
	key == KEY_LEFT ? k |= LEFT : (void)key;
	key == KEY_RIGHT ? k |= RIGHT : (void)key;
	key == KEY_D ? k ^= DEBUG : (void)key;
	key == KEY_H ? k ^= HELP : (void)key;
	*keymod = k;
	return (0);
}

int		key_release(int key, int *keymod)
{
	int		k;

	k = *keymod;
	key == KEY_DEL ? k &= OFF(RESET) : (void)key;
	key == KEY_X ? k &= OFF(MARKED_UP) : (void)key;
	key == KEY_V ? k &= OFF(MARKED_LOW) : (void)key;
	key == KEY_PLUS ? k &= OFF(PLUS) : (void)key;
	key == KEY_MINUS ? k &= OFF(MINUS) : (void)key;
	key == KEY_UP ? k &= OFF(UP) : (void)key;
	key == KEY_DOWN ? k &= OFF(DOWN) : (void)key;
	key == KEY_LEFT ? k &= OFF(LEFT) : (void)key;
	key == KEY_RIGHT ? k &= OFF(RIGHT) : (void)key;
	*keymod = k;
	return (0);
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

static void		apply_mods(t_env *e, t_scene *wld, t_mod *mod)
{
	int			k;
	int			curr_set;
	t_colors	*c;

	c = &mod->col;
	curr_set = c->curr_set;
	k = mod->keymod;
	QUIT_SET(k) ? end_session(e, NULL, EXIT_SUCCESS) : (void)k;
	RESET_SET(k) ? reset_modifiers(wld) : (void)k;
	NEXT_PROJ_SET(k) ? next_proj(mod) : (void)k;
	NEXT_COLOR_SET(k) ? next_color(wld, c, &mod->keymod) : (void)k;
	MARKED_UP_SET(k) ? (c->marked_alt[curr_set] += ALT_FACTOR) : (void)k;
	MARKED_LOW_SET(k) ? (c->marked_alt[curr_set] -= ALT_FACTOR) : (void)k;
	apply_actions(k, mod);
}

int		loop_hook(t_env *env)
{
	t_mlxwin	*win;
	t_scene		*wld;
	void		*eid;
	t_mod		*mod;

	eid = env->m_env->init_id;
	win = env->m_win;
	wld = env->world;
	mod = &(wld->mod);
	apply_mods(env, wld, mod);
	refresh_window(env);
	HELP_SET(mod->keymod) ? help_more(eid, win) : help_less(eid, win);
	DEBUG_SET(mod->keymod) ? fps_count(env, eid, win->id) : (void)env;
	return (0);
}
