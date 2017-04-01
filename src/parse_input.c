
#include "libft.h"

static int	file_to_lst(char *file, t_list **dst)
{
	int	nb_lines;
	int	fd;
	char	*buff;

	if (!dst || (fd = open(file, O_RDONLY)) < 0)
		return (ERROR);
	nb_lines = 0;
	while (get_next_line(fd, &buff) > 0)
	{
		ft_lstadd(dst, ft_lstnew(buff, ft_strlen(buff)));
		ft_strdel(&buff);
		nb_lines++;
	}
	close(fd);
	return (nb_lines);
}

static int	count_and_check(t_list *lst)
{
	int	ref_value;

	if (!lst)
		return (ERROR);
	ref_value = ft_nbwords(lst->content, ' ');
	lst = lst->next;
	while (lst)
	{
		if (ft_nbwords(lst->content, ' ') != ref_value)
			return (ERROR);
		lst = lst->next;
	}
	return (ref_value);
}

static int	end_error(t_list **lst, t_map **m)
{
	ft_memdel(map);
	ft_lstdel(lst, &ft_delcontent);
	return (ERROR);
}

int		*str_to_inttab(char *str, int nb_columns)
{
}

t_map		*input_to_map(char *file)
{
	t_list	*lst;
	t_map	*m;
	int	i;

	lst = NULL;
	m = (t_map *)ft_memalloc(sizeof(*m));
	if ((m->nb_lines = file_to_lst(file, &lst)) == ERROR)
		return (end_error(&lst));
	if ((m->nb_columns = count_and_check(lst)) == ERROR)
		return (end_error(&lst));
	m->tab = (int **)ft_memalloc(sizeof(m->(*tab)) * m->nb_lines);
	i = m->nb_lines;
	while (i-- >= 0)
	{
		m->tab[i] = str_to_inttab(lst->content, m->nb_columns);
		lst = lst->next;
	}
	ft_lstdel(lst, &ft_delcontent);
	return (m);
}
