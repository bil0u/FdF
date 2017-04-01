/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:36 by upopee            #+#    #+#             */
/*   Updated: 2017/04/01 19:15:56 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"

static void	end_error(t_list **lst, t_map **m, int i)
{
	if ((*m)->nb_lines != ERROR && (*m)->nb_columns != ERROR)
	{
		while (i < (*m)->nb_lines)
		{
			ft_memdel((void **)&((*m)->tab[i]));
			i++;
		}
	}
	ft_memdel((void **)m);
	ft_lstdel(lst, &ft_delcontent);
	exit(EXIT_FAILURE);
}

static int	file_to_lst(char *file, t_list **dst)
{
	int		nb_lines;
	int		fd;
	char	*buff;

	if (!dst || (fd = open(file, O_RDONLY)) < 0)
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

static int	count_and_check(t_list *lst)
{
	char	*str;
	int		ref_value;
	int		ret;

	if (!lst)
		return (ERROR);
	ref_value = ft_nbwords(lst->content, ' ');
	while (lst)
	{
		str = lst->content;
		if (ft_nbwords(str, ' ') != (size_t)ref_value)
			return (ERROR);
		while (*str)
		{
			if ((ret = ft_strisnumber(str, ' ')) == 0)
				return (ERROR);
			str += str[ret] ? (ret + 1) : ret;
		}
		lst = lst->next;
	}
	return (ref_value);
}

int			*str_to_inttab(char *str, int nb_columns)
{
	int		*line;
	int		i;

	if ((line = (int *)ft_memalloc(sizeof(int) * nb_columns)) == NULL)
		return (NULL);
	i = 0;
	while (i < nb_columns)
	{
		line[i] = ft_atoi(str);
		str = ft_strchr(str, ' ') + 1;
		i++;
	}
	return (line);
}

t_map		*input_to_map(char *file)
{
	t_list	*lst;
	t_list	*leak;
	t_map	*m;
	int		i;

	lst = NULL;
	i = 0;
	if ((m = (t_map *)ft_memalloc(sizeof(*m))) == NULL)
		end_error(&lst, &m, i);
	if ((m->nb_lines = file_to_lst(file, &lst)) == ERROR)
		end_error(&lst, &m, i);
	if ((m->nb_columns = count_and_check(lst)) == ERROR)
		end_error(&lst, &m, i);
	i = m->nb_lines;
	if ((m->tab = (int **)ft_memalloc(sizeof(int *) * m->nb_lines)) == NULL)
		end_error(&lst, &m, i);
	leak = lst;
	while (i-- > 0)
	{
		if ((m->tab[i] = str_to_inttab(lst->content, m->nb_columns)) == NULL)
			end_error(&lst, &m, i);
		lst = lst->next;
	}
	ft_lstdel(&leak, &ft_delcontent);
	return (m);
}

int			main(int argc, char **argv)
{
	t_map	*m;
	int		i;
	int		j;

	if (argc != 2)
	{
		ft_putendl_fd("usage : ./fdf [path/to/file]", 2);
		return (-1);
	}
	m = input_to_map(argv[1]);
	i = 0;
	while (i < m->nb_lines)
	{
		j = 0;
		while (j < m->nb_columns)
		{
			ft_printf("%d ", m->tab[i][j]);
			j++;
		}
		ft_putendl("");
		i++;
	}
	return (0);
}
