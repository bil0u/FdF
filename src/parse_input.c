/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:36 by upopee            #+#    #+#             */
/*   Updated: 2017/04/12 08:18:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"

static void			end_error(t_list **lst, t_scene **s, int i, char *msg)
{
	if (s && *s && (*s)->nb_lines != ERROR && (*s)->nb_columns != ERROR)
	{
		while (i < (*s)->nb_lines)
		{
			ft_memdel((void **)&((*s)->tab[i]));
			i++;
		}
		ft_memdel((void **)s);
	}
	ft_lstdel(lst, &ft_delcontent);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int			file_to_lst(char *file, t_list **dst)
{
	int				nb_lines;
	int				fd;
	char			*buff;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ERROR);
	nb_lines = 0;
	buff = NULL;
	while (get_next_line(fd, &buff) > 0)
	{
		ft_lstadd(dst, ft_lstnew(buff, ft_strlen(buff) + 1));
		ft_strdel(&buff);
		nb_lines++;
	}
	close(fd);
	return (nb_lines);
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

static t_vector4	*str_to_vertices(char *str, int nb_columns, int curr_line)
{
	t_vector4		*line;
	int				i;

	if (!(line = (t_vector4 *)ft_memalloc(sizeof(t_vector4) * nb_columns)))
		return (NULL);
	i = 0;
	while (i < nb_columns)
	{
		(line[i]).x = i;
		(line[i]).y = curr_line;
		(line[i]).z = ft_atoi(str);
		(line[i]).w = 1.0;
		str = ft_strchr(str, MAP_SEPARATOR) + 1;
		i++;
	}
	return (line);
}

t_scene				*input_to_scene(char *file)
{
	t_list			*lst;
	t_list			*leak;
	t_scene			*s;
	int				i;

	lst = NULL;
	i = 0;
	if (!(s = (t_scene *)malloc(sizeof(t_scene))))
		end_error(&lst, &s, i, "malloc: cannot allocate memory");
	if ((s->nb_lines = file_to_lst(file, &lst)) == ERROR)
		end_error(&lst, &s, i, "open: file does not exist");
	if ((s->nb_columns = count_and_check(lst)) == ERROR)
		end_error(&lst, &s, i, "fdf: file not valid");
	i = s->nb_lines;
	if (!(s->tab = (t_vector4 **)malloc(sizeof(t_vector4 *) * s->nb_lines)))
		end_error(&lst, &s, i, "malloc: cannot allocate memory");
	leak = lst;
	while (i-- > 0)
	{
		if (!(s->tab[i] = str_to_vertices(lst->content, s->nb_columns, i)))
			end_error(&lst, &s, i, "malloc: cannot allocate memory");
		lst = lst->next;
	}
	ft_lstdel(&leak, &ft_delcontent);
	return (s);
}
