/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:25 by upopee            #+#    #+#             */
/*   Updated: 2017/04/01 09:49:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"

void	bresenham(t_env *e, t_coord p1, t_coord p2)
{
	int	delta_x;
	int	delta_y;
	int	error;

	error = p2.x - p1.x;
	delta_x = (error << 1);
	delta_y = ((p2.y - p1.y) << 1);
	while (p1.x <= p2.x)
	{
		mlx_put_pixel(e->mlx_ptr, e->mlx_win, p1.x, p1.y, 0x00FFFFFF);
		p1.x++;
		if ((err -= delta_y) <= 0)
		{
			p1.y++;
			error += delta_x;
		}
	}
}
