/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:54:49 by upopee            #+#    #+#             */
/*   Updated: 2017/03/30 16:15:18 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"

void	ft_bresenham(t_env *e, t_coord p1, t_coord p2)
{
	int		delta_x;
	int		delta_y;
	int		err_value;
	err_value = p2.x - p1.x;
	delta_x = (err_value << 1);
	delta_y = ((p2.y - p1.y) << 1);
	while (p1.x <= p2.x)
	{
		mlx_pixel_put(e->mlx_ptr, e->win-ptr, p1.x, p1.y, 0x00FFFFFF);
		p1.x++;
		if ((err_value -= delta_y) <= 0)
		{
			p1.y++;
			err_value += delta_x;
		}
	}
}
