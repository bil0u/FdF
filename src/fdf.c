/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/12 10:04:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_env.h"
#include "parse_input.h"
#include "matrix_utils.h"

#ifdef DEBUG
#include <stdio.h>

void	print_mat4(char *name, t_matrix4 *m)
{
	printf("-- %-15s --\n", name);
	printf("{% .f % .f % .f % .f }\n", m->array[0][0], m->array[0][1], m->array[0][2], m->array[0][3]);
	printf("{% .f % .f % .f % .f }\n", m->array[1][0], m->array[1][1], m->array[1][2], m->array[1][3]);
	printf("{% .f % .f % .f % .f }\n", m->array[2][0], m->array[2][1], m->array[2][2], m->array[2][3]);
	printf("{% .f % .f % .f % .f }\n", m->array[3][0], m->array[3][1], m->array[3][2], m->array[3][3]);
	printf("---------------------\n");
}

void	print_vec4(t_vector4 *v)
{
	printf("{% .f % .f % .f }(%.f)  ", v->x, v->y, v->z, v->w);
}

void	print_scene_values(char *name, t_scene *s)
{
	int 		i;
	int 		j;
	i = 0;
	printf("-- %-15s --\n", name);
	while (i < s->nb_lines)
	{
		j = 0;
		while (j < s->nb_columns)
		{
			print_vec4(&(s->tab[i][j]));
			j++;
		}
		printf("\n");
		i++;
	}
	printf("---------------------\n");
}

#endif

int			main(int argc, char **argv)
{
	t_mlxenv	*e;
	t_scene		*s;

	if (argc != 2)
		end_session(NULL, NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	s = input_to_scene(argv[1]);
#ifdef DEBUG
	t_matrix4	m_local;
	t_matrix4	m_trans;
	t_matrix4	m_scale;
	t_matrix4	m_rot;

	m_trans = ft_gen_translate_mat4(1.0, 0.0, 0.0);
	print_mat4("Translation matrix", &m_trans);
	m_scale = ft_gen_scale_mat4(2.0, 2.0, 1.0);
	print_mat4("Scale matrix", &m_scale);
	m_rot = ft_gen_rotation_mat4(90.0, 0.0, 0.0, 1.0);
	print_mat4("Rotation matrix", &m_rot);
	m_local = ft_mat4_mul_mat4(&m_scale, &m_rot);
	m_local = ft_mat4_mul_mat4(&m_local, &m_trans);
	print_mat4("Final matrix", &m_local);
	print_scene_values("> Before <", s);
	apply_mat4_to_scene(&m_local, s);
	print_scene_values("> After <", s);
#endif

	e = init_mlxenv(s);
//	mlx_loop(e->arraylx_id);
	end_session(s, e, NULL, EXIT_SUCCESS);
	return (0);
}
