/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 01:02:58 by upopee            #+#    #+#             */
/*   Updated: 2017/07/07 03:38:44 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

int			count_and_check(t_list *lst, int *forced_colors);
t_vertex3f	*to_vertices(char *str, int width, int curr, int forced);

#endif
