/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/15 20:30:29 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_mat4_to_scene(t_matrix4 *m, t_scene *world)
{
	int			i;
	int			j;

	i = world->nb_rows;
	while (i--)
	{
		j = world->nb_columns;
		while (j--)
			world->map[i][j] = ft_mat4_mul_quat(m, &(world->map[i][j]));
	}
}
