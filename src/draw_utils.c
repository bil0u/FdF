/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/04/21 06:26:29 by upopee           ###   ########.fr       */
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
				curr_pixel[i] = (c >> (i * 8) & 0xFF);
		}
		else
		{
			j = 0;
			while (i--)
			{
				curr_pixel[i] = (c >> (j * 8)) & 0xFF;
				j++;
			}
		}
	}
}

static void		draw_map(t_env *env)
{
	t_mlximg	*img;
	t_quater	curr_point;
	char		*curr_pixel;
	int			i;
	int			j;

	img = env->m_img;
	i = env->world->height;
	while (i--)
	{
		j = env->world->width;
		while (j--)
		{
			float center_x = env->m_win->width * 0.5;
			float center_y = env->m_win->height * 0.5;

			curr_point = env->world->map[i][j];
			//ft_quat_normalize(&curr_point);
			if (curr_point.x < -env->cam->aspect_ratio || curr_point.x > env->cam->aspect_ratio || curr_point.y < -1 || curr_point.y > 1)
				break;
			float x = MIN(env->m_win->width - 1, (curr_point.x + 1) * 0.5 * env->m_win->width);
			float y = MIN(env->m_win->height - 1, (1 - (curr_point.y + 1) * 0.5) * env->m_win->height);
			mlx_pixel_put(env->m_env->init_id, env->m_win->id, x, y, 0X00FFFFFF);

		//	curr_pixel = img->center;
		//	curr_pixel += (int)(curr_point->x) * (img->bpp / 8);
		//	curr_pixel += (int)(curr_point->y) * img->sz_line;
		//	pixel_to_img(curr_pixel, env, 0x00FFFFFF);
		//	mlx_pixel_put(env->m_env->init_id, env->m_win->id,
		//					mid_x + curr_point->x, mid_y + curr_point->y, 0X0FFFFFF);
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
	if (!(env->m_img = init_mlximg(mlx->init_id, win->width, win->height)))
		end_session(env, "mlx: cannot create image", EXIT_FAILURE);
	img = env->m_img;
	draw_map(env);
	//mlx_put_image_to_window(mlx->init_id, win->id, img->id, 10, 10);
	del_mlximg(mlx->init_id, img);
	return (0);
}
