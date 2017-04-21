/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/21 06:32:31 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_mat4_to_scene(t_matrix4 *m, t_scene *world,
											t_quater (*mat4_mul)())
{
	int			i;
	int			j;

	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
			world->map[i][j] = (*mat4_mul)(m, &(world->map[i][j]));
	}
}
