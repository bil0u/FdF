/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 01:02:58 by upopee            #+#    #+#             */
/*   Updated: 2018/05/14 02:08:20 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "fdf.h"

static int	point_is_valid(char *str)
{
	int		ret;
	int		i;

	i = 0;
	ret = ft_strisnumber(str, MAP_SEPARATOR);
	if (ret == 0)
	{
		while (str[i] && str[i] != COLOR_SEPARATOR && str[i] != MAP_SEPARATOR)
			i++;
		if (str[i] == COLOR_SEPARATOR)
		{
			ret = ft_strisnumber(str, COLOR_SEPARATOR);
			if (ret > 0)
			{
				ret += ft_strishex(str + i + 1, MAP_SEPARATOR) + 1;
				return (ret);
			}
		}
		ret = 0;
	}
	return (ret);
}

static void	check_forced(int *forced_colors, char *str)
{
	if (*forced_colors == FALSE)
		*forced_colors = ft_strchr(str, COLOR_SEPARATOR) ? TRUE : FALSE;
}

int			count_and_check(t_list *lst, int *forced_colors)
{
	char			*str;
	int				ref_value;
	int				ret;

	if (!lst)
		return (ERROR);
	if ((ref_value = ft_nbwords(lst->content, MAP_SEPARATOR)) == 1)
		return (ERROR);
	while (lst)
	{
		str = lst->content;
		if (ft_nbwords(str, MAP_SEPARATOR) != (size_t)ref_value)
			return (ERROR);
		check_forced(forced_colors, str);
		while (*str)
		{
			if ((ret = point_is_valid(str)) == 0)
				return (ERROR);
			str += ret;
			while (str[0] == MAP_SEPARATOR)
				str++;
		}
		lst = lst->next;
	}
	return (ref_value);
}

static int	atohex(char *str)
{
	int				sign;
	int				res;
	int				value;

	res = 0;
	sign = (str[0] == '-' ? -1 : 1);
	if (str[0] == '-' || str[0] == '+')
		str++;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	while (ft_ishexdigit(str[0]))
	{
		if (ft_isalpha(str[0]))
			value = str[0] - (ft_islower(str[0]) ? 'a' : 'A');
		else
			value = str[0] - '0';
		res = res * 16 + value;
		str++;
	}
	return (res * sign);
}

t_vertex3f	*to_vertices(char *str, int width, int curr, int forced)
{
	t_vertex3f	*line;
	int			i;

	if (!(line = (t_vertex3f *)ft_memalloc(sizeof(t_vertex3f) * width)))
		return (NULL);
	i = 0;
	while (i < width)
	{
		line[i] = ft_to_ver3f((float)(i), (float)(ft_atoi(str)), (float)(curr));
		line[i].color = 0xFFFFFF;
		if (forced)
		{
			while (*str && str[0] != COLOR_SEPARATOR && str[0] != MAP_SEPARATOR)
				str++;
			if (str[0] == COLOR_SEPARATOR)
				line[i].color = atohex(str + 1);
		}
		str = ft_strchr(str, MAP_SEPARATOR);
		while (str && str[0] == MAP_SEPARATOR)
			str++;
		i++;
	}
	return (line);
}
