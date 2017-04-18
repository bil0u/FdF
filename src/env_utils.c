/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 02:53:28 by upopee            #+#    #+#             */
/*   Updated: 2017/04/19 00:38:40 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libgraphic.h"

void			end_session(t_env *env, char *msg, int status)
{
	int		i;

	if (env)
	{
		if (env->world)
		{
			if (env->world->map)
			{
				i = env->world->nb_rows;
				while (i-- > 0)
					free(env->world->map[i]);
				free(env->world->map);
			}
			free(env->world);
		}
		if (env->cam)
			free(env->cam);
		del_mlxwin(env->m_env->init_id, env->m_win);
		del_mlxenv(env->m_env);
		free(env);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	exit (status);
}

static void		get_winsize(t_scene *world, int *sz_x, int *sz_y)
{
	int		x;
	int		y;

	x = ((world->nb_columns * MLXWIN_DEFAULT_OFFSET) + MLXWIN_MARGEX + 1);
	y = ((world->nb_rows * MLXWIN_DEFAULT_OFFSET) + MLXWIN_MARGEY + 1);
	*sz_x = x > MLXWIN_SIZEX_MAX ? MLXWIN_SIZEX_MAX : x;
	*sz_y = y > MLXWIN_SIZEY_MAX ? MLXWIN_SIZEY_MAX : y;
}

t_env			*init_env(t_scene *world)
{
	t_env		*env;
	int			sz_x;
	int			sz_y;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		end_session(env, "malloc: cannot allocate memory", EXIT_FAILURE);
	env->world = world;
	get_winsize(world, &sz_x, &sz_y);
	if (!(env->cam = ft_init_camera_new(DFLT_VANGLE, DFLT_NEAR, DFLT_FAR)))
		end_session(env, "malloc: cannot allocate memory", EXIT_FAILURE);
	if (!(env->m_env = init_mlxenv()))
		end_session(env, "mlx: cannot connect with server", EXIT_FAILURE);
	if (!(env->m_win = init_mlxwin(env->m_env->init_id, sz_x, sz_y, "> FDF <")))
		end_session(env, "mlx: cannot create window", EXIT_FAILURE);
	return (env);
}
