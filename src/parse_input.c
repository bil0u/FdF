/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:36 by upopee            #+#    #+#             */
/*   Updated: 2017/04/27 09:37:39 by upopee           ###   ########.fr       */
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
			str += ret;
			while (str[0] == MAP_SEPARATOR)
				str++;
		}
		lst = lst->next;
	}
	return (ref_value);
}

static t_vector3	*to_vec3tab(char *str, int width, int curr)
{
	t_vector3		*line;
	int				i;

	if (!(line = (t_vector3 *)ft_memalloc(sizeof(t_vector3) * width)))
		return (NULL);
	i = 0;
	while (i < width)
	{
		line[i] = ft_to_vec3((float)(i), (float)(ft_atoi(str)), (float)(curr));
		str = ft_strchr(str, MAP_SEPARATOR);
		while (str && str[0] == MAP_SEPARATOR)
			str++;
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
	if (!(world->map = (t_vector3 **)malloc(sizeof(t_vector3 *) * i)))
		end_error(&lst, &world, i, "malloc: cannot allocate memory");
	curr = lst;
	while (i-- > 0)
	{
		if (!(world->map[i] = to_vec3tab(curr->content, world->width, i)))
			end_error(&curr, &world, i, "malloc: cannot allocate memory");
		curr = curr->next;
	}
	ft_lstdel(&lst, &ft_delcontent);
	return (world);
}
