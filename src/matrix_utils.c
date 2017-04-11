/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:19:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/11 06:53:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_matrix4f_to_scene(t_matrix4f *m, t_scene *s)
{
	int			i;
	int			j;

	i = s->nb_lines;
	while (i--)
	{
		j = s->nb_columns;
		while (j--)
			ft_matrix4f_mul_vertex4f(m, &(s->tab[i][j]));
	}
}
