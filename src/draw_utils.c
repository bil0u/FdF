/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 03:17:18 by upopee            #+#    #+#             */
/*   Updated: 2017/07/15 23:23:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "pixel_shader.h"

void				*draw_lines(void *arg)
{
	t_drawdata	tenv;
	int			i;
	int			j;
	t_vertex3f	tmp;
	t_line		line;

	tenv = *((t_drawdata *)arg);
	i = tenv.wld_h;
	while (i--)
	{
		j = tenv.wld_w;
		tmp = tenv.wld_map[i][j - 1];
		line.a = ft_ver3f_proj(tmp, tenv.final, tenv.frm_w, tenv.frm_h);
		while (--j)
		{
			tmp = tenv.wld_map[i][j - 1];
			line.b = ft_ver3f_proj(tmp, tenv.final, tenv.frm_w, tenv.frm_h);
			fastline_fdf(tenv.frame, line);
			line.a = line.b;
		}
	}
	pthread_exit(NULL);
}

void				*draw_columns(void *arg)
{
	t_drawdata	tenv;
	int			i;
	int			j;
	t_vertex3f	tmp;
	t_line		line;

	tenv = *((t_drawdata *)arg);
	j = tenv.wld_w;
	while (j--)
	{
		i = tenv.wld_h;
		tmp = tenv.wld_map[i - 1][j];
		line.a = ft_ver3f_proj(tmp, tenv.final, tenv.frm_w, tenv.frm_h);
		line.a.color = tmp.color;
		while (--i)
		{
			tmp = tenv.wld_map[i - 1][j];
			line.b = ft_ver3f_proj(tmp, tenv.final, tenv.frm_w, tenv.frm_h);
			line.b.color = tmp.color;
			fastline_fdf(tenv.frame, line);
			line.a = line.b;
		}
	}
	pthread_exit(NULL);
}

void				*draw_points(void *arg)
{
	t_drawdata	tenv;
	int			i;
	int			j;
	t_vertex3f	tmp;
	t_vertex2i	pt;

	tenv = *((t_drawdata *)arg);
	j = tenv.wld_w;
	while (j--)
	{
		i = tenv.wld_h;
		while (i--)
		{
			tmp = tenv.wld_map[i][j];
			pt = ft_ver3f_proj(tmp, tenv.final, tenv.frm_w, tenv.frm_h);
			pixel_to_img(tenv.frame, pt.x, pt.y, tmp.color);
		}
	}
	pthread_exit(NULL);
}
