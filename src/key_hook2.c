/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 03:07:14 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "key_hook.h"
#include "world_utils.h"
#include "refresh_window.h"
#include "color_utils.h"

static void		zoom(t_wldmod *mod, float zoom_value)
{
	if (mod->zoom < MIN_ZOOM && mod->zoom > MAX_ZOOM)
		mod->zoom *= zoom_value;
}

static void		next_proj(t_keymod *k, t_wldmod *w)
{
	w->proj_type = (w->proj_type + 1) % NB_PROJS;
	w->scale = ft_to_vec3(DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
	if (w->proj_type == ORTHOGRAPHIC_PROJ)
		w->scale = ft_vec3_scale(w->scale, 0.01);
	k->next_proj = 0;
}

static void		next_color(t_scene *w, t_colors *c, t_keymod *k)
{
	int		i;

	i = c->curr_set;
	if (k->full_colorset)
	{
		c->curr_set = (i + 1) % NB_COLORSETS;
		apply_color_set(w, *c);
	}
	else
	{
		c->curr_color[i] = (c->curr_color[i] + 1) % c->nb_colors[i];
		apply_simple_color(w, c->colors[i][c->curr_color[i]]);
	}
	k->next_color = 0;
}

int		key_press(int key, t_keymod *k)
{
	ft_printf("PRESSED key < %d >\n", key);
	(key == KEY_ESC || key == KEY_Q) ? k->quit = 1 : (void)key;
	(key == KEY_DEL) ? k->reset = 1 : (void)key;
	(key == KEY_R) ? k->rotate = 1 : (void)key;
	(key == KEY_T) ? k->rotate = 0 : (void)key;
	(key == KEY_Z) ? k->zoom = 1 : (void)key;
	(key == KEY_A) ? k->zoom = 0 : (void)key;
	(key == KEY_ALT_LEFT || key == KEY_ALT_RIGHT) ? k->pts_only = !k->pts_only
													: (void)key;
	(key == KEY_P) ? k->next_proj = 1 : (void)key;
	(key == KEY_SPACE) ? k->next_color = 1 : (void)key;
	(key == KEY_C) ? k->full_colorset = !k->full_colorset : (void)key;
	(key == KEY_X) ? k->up_marked_alt = 1 : (void)key;
	(key == KEY_V) ? k->low_marked_alt = 1 : (void)key;
	(key == KEY_PLUS) ? k->plus = 1 : (void)key;
	(key == KEY_MINUS) ? k->minus = 1 : (void)key;
	(key == KEY_UP) ? k->up = 1 : (void)key;
	(key == KEY_DOWN) ? k->down = 1 : (void)key;
	(key == KEY_LEFT) ? k->left = 1 : (void)key;
	(key == KEY_RIGHT) ? k->right = 1 : (void)key;
	return (0);
}

int		key_release(int key, t_keymod *k)
{
	ft_printf("RELEASED key <%d >\n", key);
	(key == KEY_DEL) ? k->reset = 0 : (void)key;
	(key == KEY_X) ? k->up_marked_alt = 0 : (void)key;
	(key == KEY_V) ? k->low_marked_alt = 0 : (void)key;
	(key == KEY_PLUS) ? k->plus = 0 : (void)key;
	(key == KEY_MINUS) ? k->minus = 0 : (void)key;
	(key == KEY_UP) ? k->up = 0 : (void)key;
	(key == KEY_DOWN) ? k->down = 0 : (void)key;
	(key == KEY_LEFT) ? k->left = 0 : (void)key;
	(key == KEY_RIGHT) ? k->right = 0 : (void)key;
	return (0);
}

int		destroy_event(t_env *env)
{
	end_session(env, NULL, EXIT_SUCCESS);
	return (0);
}

int		loop_hook(t_env *e)
{
	t_wldmod	*wm;
	t_keymod	*km;

	wm = &(e->world->mod);
	km = &(e->keymod);
	km->quit ? end_session(e, NULL, EXIT_SUCCESS) : (void)e;
	km->reset ? reset_modifiers(e->world, km) : (void)e;
	km->next_proj ? next_proj(km, wm) : (void)e;
	km->next_color ? next_color(e->world, &(wm->col), km) : (void)e;
	km->up_marked_alt ? (wm->col.marked_alt[wm->col.curr_set] += ALT_FACTOR) : (void)e;
	km->low_marked_alt ? (wm->col.marked_alt[wm->col.curr_set] -= ALT_FACTOR) : (void)e;
	if (km->plus)
		km->zoom ? zoom(wm, Z_PSPEED) : (wm->scale.y += ALT_FACTOR);
	if (km->minus)
		km->zoom ? zoom(wm, Z_MSPEED) : (wm->scale.y -= ALT_FACTOR);
	if (km->up)
		km->rotate ? (wm->rot_x += R_SPEED) : (wm->translate.z += T_SPEED);
	if (km->down)
		km->rotate ? (wm->rot_x -= R_SPEED) : (wm->translate.z -= T_SPEED);
	if (km->left)
		km->rotate ? (wm->rot_y += R_SPEED) : (wm->translate.x += T_SPEED);
	if (km->right)
		km->rotate ? (wm->rot_y -= R_SPEED) : (wm->translate.x -= T_SPEED);
	refresh_window(e);
	return (0);
}
