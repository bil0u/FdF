/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 02:56:03 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 20:55:24 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

void		end_session(t_env *env, char *msg, int status);
void		reset_modifiers(t_scene *world);
t_env		*init_env(t_scene *world);

#endif
