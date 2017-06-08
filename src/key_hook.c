/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/06/08 18:55:00 by upopee           ###   ########.fr       */
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
		mod->scale.y += 0.05;
	else
		mod->scale.y -= 0.05;
}

static void		zoom_map(int key, t_mod *mod)
{
	if (key == KEY_PLUS && mod->zoom > MAX_ZOOM)
		mod->zoom *= 0.9;
	else if (mod->zoom < MIN_ZOOM)
		mod->zoom *= 1.1;
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
		mod->rot_y += 1.0;
	else if (key == KEY_RIGHT)
		mod->rot_y -= 1.0;
	else if (key == KEY_UP)
		mod->rot_x += 1.0;
	else
		mod->rot_x -= 1.0;
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

static void		handle_color(int key, t_scene *world, t_mod *mod)
{
	if (key == KEY_C)
		mod->col.full_set = !mod->col.full_set;
	else
	{
		if (mod->col.full_set)
		{
			mod->col.curr_set = mod->col.curr_set++ % NB_COLORSETS;
			apply_color_set(world, &(mod->col), mod->col.curr_set);
		}
		else
		{
			mod->col.curr_color = mod->col.curr_color++
								% mod->col.nb_colors[mod->col.curr_set];
			apply_simple_color(world,
					mod->col.colors[mod->col.curr_set][mod->col.curr_color]);
		}
	}
}

int				key_hook(int key, t_env *env)
{
	t_mod	*mod;

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
	else if (key == KEY_SPACE || key == KEY_C)
		handle_color(key, env->world, mod);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		mod->zoom_bool == TRUE ? zoom_map(key, mod) : scale_alt_map(key, mod);
	else if (key == KEY_UP || key == KEY_DOWN
			|| key == KEY_LEFT || key == KEY_RIGHT)
		mod->rot_bool == TRUE ? rotate_map(key, mod) : translate_map(key, mod);
	refresh_window(env);
	return (0);
}
