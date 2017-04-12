/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/12 09:59:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_mat4_to_scene(t_matrix4 *m, t_scene *s)
{
	int			i;
	int			j;

	i = s->nb_lines;
	while (i--)
	{
		j = s->nb_columns;
		while (j--)
			s->tab[i][j] = ft_mat4_mul_vec4(m, &(s->tab[i][j]));
	}
}
