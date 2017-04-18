/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/04/18 17:01:44 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphic.h"
#include "fdf.h"
#include "env_utils.h"

static void		pixel_to_img(char *curr_pixel, t_env *env, int color)
{
	unsigned int	c;
	int				i;
	int				j;

	if (env->m_img->data <= curr_pixel && curr_pixel < env->m_img->limit)
	{
		c = mlx_get_color_value(env->m_env->init_id, color);
		i = env->m_img->bpp / 8;
		if (env->m_img->endian == 0)
		{
			while (i--)
				curr_pixel[i] = (unsigned char)((c >> (i * 8)) & 0xFF);
		}
		else
		{
			j = 0;
			while (i--)
				curr_pixel[i] = (unsigned char)((c >> (j++ * 8)) & 0xFF);
		}
	}
}

static void		retina_pixel_to_img(char *curr_pixel, t_env *env, int color)
{
		pixel_to_img(curr_pixel, env, color);
		pixel_to_img(curr_pixel - 1, env, color);
		pixel_to_img(curr_pixel + 1, env, color);
		pixel_to_img(curr_pixel + env->m_img->sz_line, env, color);
		pixel_to_img(curr_pixel + env->m_img->sz_line - 1, env, color);
		pixel_to_img(curr_pixel + env->m_img->sz_line + 1, env, color);
		pixel_to_img(curr_pixel - env->m_img->sz_line, env, color);
		pixel_to_img(curr_pixel - env->m_img->sz_line - 1, env, color);
		pixel_to_img(curr_pixel - env->m_img->sz_line + 1, env, color);
}

static void		draw_map(t_env *env)
{
	t_mlximg	*img;
	t_quater	*curr_point;
	char		*curr_pixel;
	int			i;
	int			j;

	img = env->m_img;
	i = env->world->nb_rows;
	while (i--)
	{
		j = env->world->nb_columns;
		while (j--)
		{
			curr_point = &(env->world->map[i][j]);
			curr_pixel = img->center;
			curr_pixel += (int)(curr_point->x) * (img->bpp / 8);
			curr_pixel += (int)(curr_point->y) * img->sz_line;
			retina_pixel_to_img(curr_pixel, env, 0x00FFFFFF);
		}
	}
}

int				refresh_window(t_env *env)
{
	t_mlxenv	*mlx;
	t_mlxwin	*win;
	t_mlximg	*img;

	mlx = env->m_env;
	win = env->m_win;
	if (!(env->m_img = init_mlximg(mlx->init_id, win->sz_x, win->sz_y)))
		end_session(env, "mlx: cannot create image", EXIT_FAILURE);
	img = env->m_img;
	draw_map(env);
	mlx_put_image_to_window(mlx->init_id, win->id, img->id, 10, 10);
	del_mlximg(mlx->init_id, img);
	return (0);
}
