/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/07/06 21:37:48 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw_utils.h"
#include "env_utils.h"
#include "clear_frame.h"

static t_matrix4	get_model_matrix(t_mod mod, t_matrix4 center_matrix)
{
	t_matrix4	scale;
	t_matrix4	rotate;
	t_matrix4	translate;
	t_matrix4	model;

	scale = ft_gen_scale_mat4(mod.scale);
	rotate = ft_gen_euler_rotation_mat4(mod.rot_x, mod.rot_y, mod.rot_z);
	translate = ft_gen_translate_mat4(mod.translate);
	model = ft_mat4_mul_mat4(scale, center_matrix);
	model = ft_mat4_mul_mat4(rotate, model);
	model = ft_mat4_mul_mat4(translate, model);
	return (model);
}

static t_matrix4	get_mvp_matrix(t_camera *cam, t_scene *wld)
{
	t_matrix4	model;
	t_matrix4	view;
	t_matrix4	projection;
	t_matrix4	mvp;

	model = get_model_matrix(wld->mod, wld->center_matrix);
	view = ft_lookat(cam, wld->mod.cam_eye, wld->mod.cam_to, wld->mod.cam_upv);
	if (wld->mod.proj_type == PERSPECTIVE_PROJ)
		projection = ft_persproj_mat4(cam->view_angle * wld->mod.zoom,
										cam->near, cam->far, cam->aspect_ratio);
	else
		projection = ft_orthoproj_mat4(cam->view_angle * wld->mod.zoom,
										cam->near, cam->far, cam->aspect_ratio);
	mvp = ft_mat4_mul_mat4(view, model);
	mvp = ft_mat4_mul_mat4(projection, mvp);
	return (mvp);
}

static void		fill_frame(t_env *env, t_mlximg *img)
{
	t_matrix4		final;
	t_scene			*wld;

	wld = env->world;
	final = get_mvp_matrix(env->cam, wld);
	if (!PTS_ONLY_SET(wld->mod.keymod))
	{
		draw_lines(wld, img, final);
		draw_columns(wld, img, final);
	}
	else
		draw_points(wld, img, final);
}

int				refresh_window(t_env *env)
{
	t_mlxfbuf		*fbuf;
	t_mlxwin		*win;
	t_mlximg		*img;
	int				curr_frame;

	fbuf = env->m_fbuf;
	win = env->m_win;
	curr_frame = fbuf->curr;
	img = &(fbuf->frame[curr_frame]);
	fill_frame(env, img);
	mlx_put_image_to_window(env->m_env->init_id, win->id, img->id, 0, 0);
	clear_frame(img->data, img->sz_line * img->height);
	fbuf->curr = (curr_frame + 1) == fbuf->nb_frames ? 0 : (curr_frame + 1);
	return (0);
}
