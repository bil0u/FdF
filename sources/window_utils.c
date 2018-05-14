/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/07/26 20:00:40 by lduval           ###   ########.fr       */
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
	translate = ft_gen_translate_mat4(mod.trans);
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

static void			fill_frame(t_drawdata tenv)
{
	t_threads4		thds;

	if (!PTS_ONLY_SET((tenv.world->mod.keymod)))
	{
		pthread_create(&thds.t0, NULL, &draw_lines, &tenv);
		pthread_create(&thds.t1, NULL, &draw_columns, &tenv);
		pthread_join(thds.t0, NULL);
		pthread_join(thds.t1, NULL);
	}
	else
	{
		pthread_create(&thds.t0, NULL, &draw_points, &tenv);
		pthread_join(thds.t0, NULL);
	}
}

static t_drawdata	init_threadenv(t_env e, t_scene w)
{
	t_drawdata		tenv;

	tenv.win = e.m_win;
	tenv.world = e.world;
	tenv.wld_map = w.map;
	tenv.wld_w = w.width;
	tenv.wld_h = w.height;
	tenv.final = get_mvp_matrix(e.cam, tenv.world);
	return (tenv);
}

int					refresh_window(t_env *env)
{
	t_mlxfbuf	*fbuf;
	t_mlximg	frm;
	int			i;
	t_drawdata	tenv;

	tenv = init_threadenv(*env, *(env->world));
	fbuf = env->m_fbuf;
	i = fbuf->curr;
	tenv.frame = &(fbuf->frame[i]);
	frm = fbuf->frame[i];
	tenv.frm_w = frm.width;
	tenv.frm_h = frm.height;
	fill_frame(tenv);
	mlx_put_image_to_window(env->m_env->init_id, env->m_win->id, frm.id, 0, 0);
	clear_frame(frm.data, frm.sz_line * frm.height);
	fbuf->curr = (i + 1) == FPS_BUFF_SIZE ? 0 : i + 1;
	return (0);
}
