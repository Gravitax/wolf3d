/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/25 19:46:54 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void        ft_mouse_motion_x(t_wolf *data)
{
	float factor;
	float an_2;

	factor = 0.75;
	an_2 = (float)(data->mouse.xrel / factor);
	data->player.angle += data->player.speed
			* data->etime * data->player.ms * an_2;
}