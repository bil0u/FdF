/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:36 by upopee            #+#    #+#             */
/*   Updated: 2017/07/07 04:58:06 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"
#include "parse_utils.h"

int			file_to_lst(char *file, t_list **dst)
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

void		end_error(t_list **lst, t_scene **world, int i, char *msg)
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

t_scene				*input_to_scene(char *file)
{
	t_list			*l;
	t_list			*c;
	t_scene			*w;
	int				i;

	l = NULL;
	if (!(w = (t_scene *)malloc(sizeof(t_scene))))
		end_error(&l, &w, 0, "malloc: cannot allocate memory");
	if ((w->height = file_to_lst(file, &l)) == ERROR)
		end_error(&l, &w, 0, "open: file does not exist");
	w->mod.force_c = 0;
	if ((w->width = count_and_check(l, &w->mod.force_c)) == ERROR)
		end_error(&l, &w, 0, "fdf: file not valid");
	i = w->height;
	if (!(w->map = (t_vertex3f **)malloc(sizeof(t_vertex3f *) * i)))
		end_error(&l, &w, 0, "malloc: cannot allocate memory");
	c = l;
	while (i-- > 0)
	{
		if (!(w->map[i] = to_vertices(c->content, w->width, i, w->mod.force_c)))
			end_error(&c, &w, i, "malloc: cannot allocate memory");
		c = c->next;
	}
	ft_lstdel(&l, &ft_delcontent);
	return (w);
}
