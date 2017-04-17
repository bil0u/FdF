/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/04/18 01:18:03 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphic.h"
#include "fdf.h"
#include "env_utils.h"

static void		fill_little_endian(char *data, int bpp, unsigned int color)
{
	unsigned int	mask;

	mask = 0xFF;
	while (bpp--)
	{
		*data = color & mask;
		data++;
		mask = mask << 8;
	}
}

static void		fill_big_endian(char *data, int bpp, unsigned int color)
{
	unsigned int	mask;

	mask = 0xFF << ((bpp - 1) * 8);
	while (bpp--)
	{
		*data = color & mask;
		data++;
		mask = mask >> 8;
	}
}

static void		pixel_to_img(char *curr, t_env *env, int color)
{
	unsigned int	c;

	c = mlx_get_color_value(env->m_env->init_id, color);
	if (env->m_img->endian == 0)
		fill_little_endian(curr, env->m_img->bpp, c);
	else
		fill_big_endian(curr, env->m_img->bpp, c);
}

static void		draw_map(t_env *env)
{
	char			*curr;
	int		i;
	int		j;

	curr = env->m_img->data;
	i = env->world->nb_columns;
	while (i--)
	{
		j = env->world->nb_rows;
		while (j--)
		{
			pixel_to_img(curr, env, 0x00FFFFFF);
			curr += env->m_img->bpp;
		}
	}
}

int				refresh_window(t_env *env)
{
	t_mlxwin	*w;
	t_mlximg	*i;
	t_mlxenv	*e;

	w = env->m_win;
	e = env->m_env;
	if (!(env->m_img = init_mlximg(e->init_id, w->sz_x, w->sz_y)))
		end_session(env, "mlx: cannot create image", EXIT_FAILURE);
	i = env->m_img;
	draw_map(env);
	mlx_put_image_to_window(e->init_id, w->id, i->id, 0, 0);
	del_mlximg(e->init_id, i);
	return (0);
}
