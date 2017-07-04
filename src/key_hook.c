/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/07/01 14:07:43 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "key_hook.h"
#include "world_utils.h"
#include "refresh_window.h"
#include "color_utils.h"

static void		scale_alt_map(int key, t_mod *mod)
{
	if (key == KEY_PLUS)
		mod->scale.y += ALT_FACTOR;
	else
		mod->scale.y -= ALT_FACTOR;
}

static void		zoom_map(int key, t_mod *mod)
{
	if (key == KEY_PLUS && mod->zoom > MAX_ZOOM)
		mod->zoom *= ZOOM_PLUS_SPEED;
	else if (mod->zoom < MIN_ZOOM)
		mod->zoom *= ZOOM_MINUS_SPEED;
}

static void		translate_map(int key, t_mod *mod)
{
	if (key == KEY_UP)
		mod->translate.z += 2.0;
	else if (key == KEY_DOWN)
		mod->translate.z -= 2.0;
	else if (key == KEY_LEFT)
		mod->translate.x += 2.0;
	else
		mod->translate.x -= 2.0;
}

static void		rotate_map(int key, t_mod *mod)
{
	if (key == KEY_LEFT)
		mod->rot_y += ROT_SPEED;
	else if (key == KEY_RIGHT)
		mod->rot_y -= ROT_SPEED;
	else if (key == KEY_UP)
		mod->rot_x += ROT_SPEED;
	else
		mod->rot_x -= ROT_SPEED;
}

static void		change_projection(int key, t_mod *mod)
{
	if (key == KEY_P)
	{
		mod->proj_type = PERSPECTIVE_PROJ;
		mod->scale = ft_to_vec3(DEFAULT_SCALE_X,
										DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
	}
	else
	{
		mod->proj_type = ORTHOGRAPHIC_PROJ;
		mod->scale = ft_to_vec3(DEFAULT_SCALE_X,
										DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
		mod->scale = ft_vec3_scale(mod->scale, 0.01);
	}
}

static void		switch_controls(int key, t_mod *mod)
{
	if (key == KEY_R)
		mod->rot_bool = TRUE;
	else if (key == KEY_T)
		mod->rot_bool = FALSE;
	else if (key == KEY_Z)
		mod->zoom_bool = TRUE;
	else if (key == KEY_A)
		mod->zoom_bool = FALSE;
	else if (key == KEY_ALT_LEFT || key == KEY_ALT_RIGHT)
		mod->points_only = !mod->points_only;

}

static void		handle_color(int key, t_scene *w, t_mod *m)
{
	int		i;

	i = m->col.curr_set;
	if (key == KEY_X)
		m->col.marked_alt[i] -= ALT_FACTOR;
	else if (key == KEY_V)
		m->col.marked_alt[i] += ALT_FACTOR;
	else if (key == KEY_C)
		m->col.full_set = !m->col.full_set;
	if (m->col.full_set)
	{
		if (key == KEY_SPACE)
			m->col.curr_set = (i + 1) % NB_COLORSETS;
		apply_color_set(w, m->col);
	}
	else
	{
		if (key == KEY_SPACE)
			m->col.curr_color[i] = (m->col.curr_color[i] + 1)
									% m->col.nb_colors[i];
		apply_simple_color(w, m->col.colors[i][m->col.curr_color[i]]);
	}
}

int				key_hook(int key, t_env *env)
{
	t_mod	*mod;

	ft_printf("key %d\n", key);
	mod = &(env->world->mod);
	if (key == KEY_ESC || key == KEY_Q)
		end_session(env, NULL, EXIT_SUCCESS);
	else if (key == KEY_DEL)
		reset_modifiers(env->world);
	else if (key == KEY_R || key == KEY_T || key == KEY_Z || key == KEY_A ||
			key == KEY_ALT_LEFT || key == KEY_ALT_RIGHT)
		switch_controls(key, mod);
	else if (key == KEY_P || key == KEY_O)
		change_projection(key, mod);
	else if (key == KEY_SPACE || key == KEY_C || key == KEY_X || key == KEY_V)
		handle_color(key, env->world, mod);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		mod->zoom_bool == TRUE ? zoom_map(key, mod) : scale_alt_map(key, mod);
	else if (key == KEY_UP || key == KEY_DOWN
			|| key == KEY_LEFT || key == KEY_RIGHT)
		mod->rot_bool == TRUE ? rotate_map(key, mod) : translate_map(key, mod);
	refresh_window(env);
	return (0);
}
