/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/07/09 22:06:31 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "help_utils.h"
#include "debug_utils.h"
#include "hook_utils.h"
#include "keyboard_fr.h"
#include "window_utils.h"

static void		press_1(int key, int *keymod)
{
	int		k;

	k = *keymod;
	(key == KEY_ALT_LEFT || key == KEY_ALT_RIGHT) ? k ^= PTS_ONLY : (void)key;
	key == KEY_C ? k ^= FULL_SET : (void)key;
	(key == KEY_ESC || key == KEY_Q) ? k |= QUIT : (void)key;
	key == KEY_DEL ? k |= RESET : (void)key;
	key == KEY_R ? k |= ROTATE : (void)key;
	key == KEY_T ? k &= OFF(ROTATE) : (void)key;
	key == KEY_Z ? k |= ZOOM : (void)key;
	key == KEY_A ? k &= OFF(ZOOM) : (void)key;
	key == KEY_P ? k |= NEXT_PROJ : (void)key;
	key == KEY_SPACE ? k |= NEXT_COLOR : (void)key;
	key == KEY_V ? k |= MARKED_UP : (void)key;
	key == KEY_X ? k |= MARKED_LOW : (void)key;
	key == KEY_PLUS ? k |= PLUS : (void)key;
	key == KEY_MINUS ? k |= MINUS : (void)key;
	key == KEY_UP ? k |= UP : (void)key;
	key == KEY_DOWN ? k |= DOWN : (void)key;
	key == KEY_LEFT ? k |= LEFT : (void)key;
	key == KEY_RIGHT ? k |= RIGHT : (void)key;
	key == KEY_D ? k ^= DEBUG : (void)key;
	key == KEY_H ? k ^= HELP : (void)key;
	key == KEY_U ? k |= UNFORCE_COLOR : (void)key;
	*keymod = k;
}

int		key_press(int key, int *keymod)
{
	press_1(key, keymod);
	return (0);
}

int		key_release(int key, int *keymod)
{
	int		k;

	k = *keymod;
	key == KEY_DEL ? k &= OFF(RESET) : (void)key;
	key == KEY_X ? k &= OFF(MARKED_LOW) : (void)key;
	key == KEY_V ? k &= OFF(MARKED_UP) : (void)key;
	key == KEY_PLUS ? k &= OFF(PLUS) : (void)key;
	key == KEY_MINUS ? k &= OFF(MINUS) : (void)key;
	key == KEY_UP ? k &= OFF(UP) : (void)key;
	key == KEY_DOWN ? k &= OFF(DOWN) : (void)key;
	key == KEY_LEFT ? k &= OFF(LEFT) : (void)key;
	key == KEY_RIGHT ? k &= OFF(RIGHT) : (void)key;
	*keymod = k;
	return (0);
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
