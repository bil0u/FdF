/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 02:53:28 by upopee            #+#    #+#             */
/*   Updated: 2018/05/14 02:12:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include "libgraphic.h"
#include "world_utils.h"
#include "color_utils.h"
#include "hook_utils.h"

void			end_session(t_env *env, char *msg, int status)
{
	int		i;

	if (env)
	{
		if (env->world)
		{
			if (env->world->map)
			{
				i = env->world->height;
				while (i-- > 0)
					free(env->world->map[i]);
				free(env->world->map);
			}
			free(env->world);
		}
		if (env->cam)
			free(env->cam);
		del_mlxwin(env->m_env->init_id, env->m_win);
		del_mlxfbuf(env->m_env->init_id, env->m_fbuf);
		del_mlxenv(env->m_env);
		free(env);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(status);
}

static void		get_winsize(t_scene *world, int *width, int *height)
{
	int		x;
	int		y;

	x = ((world->width * MLXWIN_DEFAULT_OFFSET) + MLXWIN_MARGEX + 1);
	y = ((world->height * MLXWIN_DEFAULT_OFFSET) + MLXWIN_MARGEY + 1);
	*width = x > MLXWIN_WIDTH_MAX ? MLXWIN_WIDTH_MAX : x;
	*height = y > MLXWIN_HEIGHT_MAX ? MLXWIN_HEIGHT_MAX : y;
}

void			reset_modifiers(t_scene *world)
{
	t_mod		m;

	get_cam_pos(world);
	m = world->mod;
	init_colors(&m.col);
	m.keymod = 0;
	if (m.force_c == FALSE)
		apply_colorset(world, m.col);
	m.keymod |= ROTATE;
	m.keymod |= ZOOM;
	m.keymod |= FULL_SET;
	m.keymod |= MARKED_SET;
	m.proj_type = PERSPECTIVE_PROJ;
	m.rot_x = DEFAULT_ROT_X;
	m.rot_y = DEFAULT_ROT_Y;
	m.rot_z = DEFAULT_ROT_Z;
	m.zoom = DEFAULT_ZOOM;
	m.trans = ft_to_vec3(0.0, 0.0, 0.0);
	m.scale = ft_to_vec3(DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_SCALE_Z);
	m.scale.y *= alt_reducer(world->alt_range);
	world->mod = m;
}

t_env			*init_env(t_scene *world)
{
	t_env		*env;
	int			width;
	int			height;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		end_session(env, "malloc: cannot allocate memory", FAILURE);
	env->world = world;
	get_alt_range(world);
	center_scene(world);
	get_winsize(world, &width, &height);
	reset_modifiers(world);
	if (!(env->cam = ft_init_cam_new(DFLT_VANGLE, (float)width / (float)height,
										DFLT_NEAR, DFLT_FAR)))
		end_session(env, "malloc: cannot allocate memory", FAILURE);
	if (!(env->m_env = init_mlxenv()))
		end_session(env, "mlx: cannot connect with server", FAILURE);
	if (!(env->m_fbuf = init_mlxfbuf(env->m_env->init_id, FPS_BUFF_SIZE,
									width, height)))
		end_session(env, "mlx: cannot create image", FAILURE);
	if (!(env->m_win = init_mlxwin(env->m_env->init_id,
									width, height, "> FDF <")))
		end_session(env, "mlx: cannot create window", FAILURE);
	return (env);
}
