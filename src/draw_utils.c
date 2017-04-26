/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/04/27 00:45:49 by upopee           ###   ########.fr       */
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

static t_matrix4	get_model_matrix(t_scene *world)
{
	t_matrix4	scale;
	t_matrix4	rotate;
	t_matrix4	translate;
	t_matrix4	model;

	scale = ft_gen_scale_mat4(world->mod.scale);
	rotate = ft_gen_rotation_mat4(world->mod.rot_angle, world->mod.rot_axis);
	translate = ft_gen_translate_mat4(world->mod.translate);
	model = ft_mat4_mul_mat4(scale, rotate);
	model = ft_mat4_mul_mat4(translate, model);
	return (model);
}

static t_matrix4	get_mvp_matrix(t_env *env)
{
	t_matrix4	model;
	t_matrix4	view;
	t_matrix4	projection;
	t_matrix4	mvp;

	model = get_model_matrix(env->world);
	view = ft_lookat(env->cam, env->world->mod.cam_eye,
					env->world->mod.cam_to, env->world->mod.cam_upv);
	projection = ft_persproj_mat4(env->cam->view_angle, env->cam->near,
									env->cam->far, env->cam->aspect_ratio);
	mvp = ft_mat4_mul_mat4(view, model);
	mvp = ft_mat4_mul_mat4(projection, mvp);
	return (mvp);
}

static t_vertex2i	vertex_proj(t_mlximg *img, t_matrix4 mat,
								t_vector3 vec, t_vertex2i origin)
{
	t_quater	hom_v;
	t_vector3	ndc_v;
	t_vertex2i	proj_v;

	hom_v = ft_vec3_to_quat(vec, 1.0);
	hom_v = ft_mat4_postmul_quat(hom_v, mat);
	ndc_v = ft_quat_to_vec3(hom_v);
	proj_v = ft_viewport_tlc(ndc_v, origin, img->width, img->height);
	return(proj_v);
}

static void		draw_map(t_env *env)
{
	t_matrix4	final_transform;
	t_vertex2i	proj_v;
	int			i;
	int			j;

	final_transform = get_mvp_matrix(env);
	i = env->world->height;
	while (i--)
	{
		j = env->world->width;
		while (j--)
		{
			proj_v = vertex_proj(env->m_img, final_transform,
									env->world->map[i][j], ft_to_ver2i(0, 0));
			mlx_pixel_put(env->m_env->init_id, env->m_win->id,
							proj_v.x, proj_v.y, 0X00FFFFFF);
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
	mlx_clear_window(mlx->init_id, win->id);
	draw_map(env);
	//mlx_put_image_to_window(mlx->init_id, win->id, img->id, 10, 10);
	del_mlximg(mlx->init_id, img);
	return (0);
}
