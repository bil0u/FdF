/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:36 by upopee            #+#    #+#             */
/*   Updated: 2017/04/21 06:27:25 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "libgraphic.h"
#include "fdf.h"

static void			end_error(t_list **lst, t_scene **world, int i, char *msg)
{
	if (world && *world
				&& (*world)->height != ERROR && (*world)->width != ERROR)
	{
		while (i < (*world)->height)
		{
			ft_memdel((void **)&((*world)->map[i]));
			i++;
		}
		ft_memdel((void **)world);
	}
	ft_lstdel(lst, &ft_delcontent);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int			file_to_lst(char *file, t_list **dst)
{
	int				height;
	int				fd;
	char			*buff;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ERROR);
	height = 0;
	buff = NULL;
	while (get_next_line(fd, &buff) > 0)
	{
		ft_lstadd(dst, ft_lstnew(buff, ft_strlen(buff) + 1));
		ft_strdel(&buff);
		height++;
	}
	close(fd);
	return (height);
}

static int			count_and_check(t_list *lst)
{
	char			*str;
	int				ref_value;
	int				ret;

	if (!lst)
		return (ERROR);
	ref_value = ft_nbwords(lst->content, MAP_SEPARATOR);
	while (lst)
	{
		str = lst->content;
		if (ft_nbwords(str, MAP_SEPARATOR) != (size_t)ref_value)
			return (ERROR);
		while (*str)
		{
			if ((ret = ft_strisnumber(str, MAP_SEPARATOR)) == 0)
				return (ERROR);
			str += str[ret] ? (ret + 1) : ret;
		}
		lst = lst->next;
	}
	return (ref_value);
}

static float		get_z_midvalue(t_scene *world)
{
	t_quater	*curr;
	float		z_min;
	float		z_max;
	int			i;
	int			j;

	z_min = (world->map[0][0]).z;
	z_max = z_min;
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			curr = world->map[i] + j;
			if (curr->z < z_min)
				z_min = curr->z;
			else if (curr->z > z_max)
				z_max = curr->z;
		}
	}
	return ((z_max - z_min) * Z_SCALE / 2.0f);
}

void			center_scene(t_scene *world)
{
	t_quater	center;
	t_quater	*curr;
	int			i;
	int			j;

	center.x = (float)(world->width - 1) * X_SCALE / 2.0f;
	center.y = (float)(world->height - 1) * Y_SCALE / 2.0f;
	center.z = get_z_midvalue(world);
	center.w = 1.0;
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			curr = world->map[i] + j;
			curr->x -= center.x;
			curr->y -= center.y;
			curr->z -= center.z;
		}
	}
}

static t_quater	*to_quattab(char *str, int width, int curr)
{
	t_quater		*line;
	int				i;

	if (!(line = (t_quater *)ft_memalloc(sizeof(t_quater) * width)))
		return (NULL);
	i = 0;
	while (i < width)
	{
		line[i] = ft_to_quat((float)(i * X_SCALE),
							(float)(curr * Y_SCALE),
							(float)(ft_atoi(str) * Z_SCALE),
							1.0f);
		str = ft_strchr(str, MAP_SEPARATOR) + 1;
		i++;
	}
	return (line);
}

t_scene				*input_to_scene(char *file)
{
	t_list			*lst;
	t_list			*curr;
	t_scene			*world;
	int				i;

	lst = NULL;
	i = 0;
	if (!(world = (t_scene *)malloc(sizeof(t_scene))))
		end_error(&lst, &world, i, "malloc: cannot allocate memory");
	if ((world->height = file_to_lst(file, &lst)) == ERROR)
		end_error(&lst, &world, i, "open: file does not exist");
	if ((world->width = count_and_check(lst)) == ERROR)
		end_error(&lst, &world, i, "fdf: file not valid");
	i = world->height;
	if (!(world->map = (t_quater **)malloc(sizeof(t_quater *) * i)))
		end_error(&lst, &world, i, "malloc: cannot allocate memory");
	curr = lst;
	while (i-- > 0)
	{
		if (!(world->map[i] = to_quattab(curr->content, world->width, i)))
			end_error(&curr, &world, i, "malloc: cannot allocate memory");
		curr = curr->next;
	}
	ft_lstdel(&lst, &ft_delcontent);
	return (world);
}
