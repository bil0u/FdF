/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 03:17:18 by upopee            #+#    #+#             */
/*   Updated: 2017/06/28 01:46:23 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "pixel_shader.h"

static t_vertex2i	v3f_proj(t_vertex3f v, t_matrix4 m, int width, int height)
{
	t_quater	clip;
	t_vector3	ndc;
	t_vertex2i	proj;

	clip = ft_to_quat(v.x, v.y, v.z, 1.0);
	clip = ft_mat4_postmul_quat(clip, m);
	ndc = ft_quat_to_vec3(clip);
	proj = ft_viewport_tlc(ndc, ft_to_ver2i(0, 0), width, height);
	return(proj);
}

void				draw_lines(t_scene *w, t_mlximg *img, t_matrix4 f)
{
	int			i;
	int			j;
	t_vertex3f	tmp;
	t_line		line;

	i = w->height;
	while (i--)
	{
		j = w->width;
		tmp = w->map[i][j - 1];
		line.a = v3f_proj(tmp, f, img->width, img->height);
		line.a.color = tmp.color;
		while (--j)
		{
			tmp = w->map[i][j - 1];
			line.b = v3f_proj(tmp, f, img->width, img->height);
			line.b.color = tmp.color;
			fastline_fdf_one_color(img, line, line.a.color);
			line.a = line.b;
		}
	}
}

void				draw_columns(t_scene *w, t_mlximg *img, t_matrix4 f)
{
	int			i;
	int			j;
	t_vertex3f	tmp;
	t_line		line;

	j = w->width;
	while (j--)
	{
		i = w->height;
		tmp = w->map[i - 1][j];
		line.a = v3f_proj(tmp, f, img->width, img->height);
		line.a.color = tmp.color;
		while (--i)
		{
			tmp = w->map[i - 1][j];
			line.b = v3f_proj(tmp, f, img->width, img->height);
			line.b.color = tmp.color;
			fastline_fdf_one_color(img, line, line.a.color);
			line.a = line.b;
		}
	}
}

void				draw_points(t_scene *w, t_mlximg *img, t_matrix4 f)
{
	int			i;
	int			j;
	t_vertex3f	tmp;
	t_vertex2i	pt;

	j = w->width;
	while (j--)
	{
		i = w->height;
		while (i--)
		{
			tmp = w->map[i][j];
			pt = v3f_proj(tmp, f, img->width, img->height);
			pixel_to_img(img, pt.x, pt.y, tmp.color);
		}
	}
}
