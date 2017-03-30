/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:17:52 by upopee            #+#    #+#             */
/*   Updated: 2017/03/30 17:04:57 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int				**parse_input_file(const char *file)
{
	char	*tmp;
	char	*leak;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = NULL;
	while (get_next_line(fd, &leak) > 0)
	{
		ft_strjoin(tmp, leak);
		ft_strdel(&leak);
	}
	close(fd);
	printf(tmp);
	ft_strdel(&tmp);
}

int		main(int argv, char **argv)
{
	if (argv != 2)
		return (1);
	parse_input_file(argv[1]);
	return (0);
}
