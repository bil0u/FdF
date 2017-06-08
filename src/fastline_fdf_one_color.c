/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fastline_fdf_one_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:57:17 by upopee            #+#    #+#             */
/*   Updated: 2017/06/05 04:51:40 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		case_one(t_mlximg *img, t_line line, int color)
{
	int		index;

	index = 0x8000 + (line.a.x << 16);
	if (line.long_len > 0)
	{
		line.long_len += line.a.y;
		while (line.a.y <= line.long_len)
		{
			pixel_to_img(img, (index >> 16), line.a.y, color);
			index += line.increment;
			(line.a.y)++;
		}
	}
	else
	{
		line.long_len += line.a.y;
		while (line.a.y >= line.long_len)
		{
			pixel_to_img(img, (index >> 16), line.a.y, color);
			index -= line.increment;
			(line.a.y)--;
		}
	}
}

static void		case_two(t_mlximg *img, t_line line, int color)
{
	int		index;

	index = 0x8000 + (line.a.y << 16);
	if (line.long_len > 0)
	{
		line.long_len += line.a.x;
		while (line.a.x <= line.long_len)
		{
			pixel_to_img(img, line.a.x, (index >> 16), color);
			index += line.increment;
			(line.a.x)++;
		}
	}
	else
	{
		line.long_len += line.a.x;
		while (line.a.x >= line.long_len)
		{
			pixel_to_img(img, line.a.x, (index >> 16), color);
			index -= line.increment;
			(line.a.x)--;
		}
	}
}

void			fastline_fdf_one_color(t_mlximg *img, t_line line, int color)
{
   	int		y_longer;
	int		short_len;
	int		swap;

	y_longer = 0;
	short_len = line.b.y - line.a.y;
	line.long_len = line.b.x - line.a.x;
	if (ABS(short_len) > ABS(line.long_len))
	{
		swap = short_len;
		short_len = line.long_len;
		line.long_len = swap;
		y_longer = 1;
	}
	line.increment = line.long_len == 0 ? 0 : (short_len << 16) / line.long_len;
	if (y_longer)
		case_one(img, line, color);
	else
		case_two(img, line, color);
}
