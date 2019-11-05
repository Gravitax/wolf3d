/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 17:23:49 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int      hitbox(t_wolf *data)
{
    int     i;
    int     range;

    range = W_WIDTH / 4 / data->monster->data.dst_fromplayer
        + data->player.wdata[data->player.weapon].hitbox;
    i = W_WIDTH / 2 - range - 1;
    if (data->monster->data.mid < W_WIDTH / 2 + range
    && data->monster->data.mid > W_WIDTH / 2 - range)
    {
        while (++i < W_WIDTH / 2 + range)
            if (data->map.depth_buffer[i] < data->monster->data.dst_fromplayer)
                return (0);
        return (1);
    }
    else
        return (0);
}

static void     shoot_impact(t_wolf *data)
{
    t_object    *head;

    head = data->monster;
    while (data->monster)
    {
        if (fabs(data->monster->data.angle) < data->player.fov / 2
        && data->monster->data.dst_fromplayer < data->map.depth)
        {
            if (hitbox(data) == 1)
            {
                data->monster->hp = data->monster->hp
                    - data->player.wdata[data->player.weapon].damage;
                if (data->monster->hp < 1)
                {
                    ++data->kill_score;
                    data->monster->dead = 1;
                }
                break ;
            }
        }
        data->monster = data->monster->next;
    }
    data->monster = head;
}

void            shoot(t_wolf *data)
{
    ++data->fire;
    if (data->fire < 10 && data->event.type == SDL_KEYDOWN)
    {
        if (data->player.weapon == 0)
            data->player.wdata[data->player.weapon].si = GUN + 1;
        else if (data->player.weapon == 1)
            data->player.wdata[data->player.weapon].si = SHOTGUN + 1;
        else if (data->player.weapon == 2)
            data->player.wdata[data->player.weapon].si = AUTOGUN + 1;
        shoot_impact(data);
    }
	else
    {
		if (data->player.weapon == 0)
            data->player.wdata[data->player.weapon].si = GUN;
        else if (data->player.weapon == 1)
            data->player.wdata[data->player.weapon].si = SHOTGUN;
        else if (data->player.weapon == 2)
            data->player.wdata[data->player.weapon].si = AUTOGUN;
        if (data->fire > 20 || data->event.type == SDL_KEYUP)
            data->fire = 0;
    }
    data->key[KSPC] = 0;
}
