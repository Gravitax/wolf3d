/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/12/14 01:15:53 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void				get_obj_calc2(t_object *l)
{
	l->data.spriteHeight = abs((int)(W_HEIGHT / (l->data.transformy)));
	l->data.drawStartY = -l->data.spriteHeight / 2 + W_HEIGHT / 2;
	if (l->data.drawStartY < 0)
		l->data.drawStartY = 0;
	l->data.drawEndY = l->data.spriteHeight / 2 + W_HEIGHT / 2;
	if (l->data.drawEndY >= W_HEIGHT)
		l->data.drawEndY = W_HEIGHT - 1;
	l->data.spriteWidth = abs((int)(W_HEIGHT / l->data.transformy));
	l->data.drawStartX = -l->data.spriteWidth / 2 + l->data.spriteScreenX;
	if (l->data.drawStartX < 0)
		l->data.drawStartX = 0;
	l->data.drawEndX = l->data.spriteWidth / 2 + l->data.spriteScreenX;
	if (l->data.drawEndX >= W_WIDTH)
		l->data.drawEndX = W_WIDTH - 1;
	l->data.mid = (l->data.drawStartX / 2) + (l->data.drawEndX / 2);
}

static void				get_obj_calc(t_wolf *d, t_object *l)
{
	float	spritex;
	float	spritey;

	l->data.dst_fromplayer = distance_calc(d->player.x, d->player.y,
		l->x, l->y);
	spritex = l->x - d->player.x;
	spritey = l->y - d->player.y;
	l->data.invDet = 1.0 / (d->player.planex * d->player.diry 
		- d->player.dirx * d->player.planey); 
	l->data.transformx = l->data.invDet * (d->player.diry * spritex
		- d->player.dirx * spritey);
	l->data.transformy = l->data.invDet * (-d->player.planey * spritex
		+ d->player.planex * spritey);
	l->data.spriteScreenX = (int)((W_WIDTH / 2) * (1 + l->data.transformx
		/ l->data.transformy));
	get_obj_calc2(l);
}

static void		display_object(t_wolf *d, t_object *l)
{
	int			sx;
	int			sy;
	int			p;
	int			texY;
	int			texX;
	uint32_t	pixel;

	sx = l->data.drawStartX;
	while (sx < l->data.drawEndX)
	{
		texX = (int)(256 * (sx - (-((int)l->data.spriteWidth) / 2
			+ l->data.spriteScreenX))
				* l->sprite.img->w / l->data.spriteWidth) / 256; 
		if (l->data.transformy > 0 && sx > 0 && sx < W_WIDTH
		&& l->data.transformy < d->map.depth_buffer[sx])
		{
			sy = l->data.drawStartY;
			while (sy < l->data.drawEndY)
			{
				p = (sy) * 256 - W_HEIGHT * 128 + l->data.spriteHeight * 128;
				texY = ((p * l->sprite.img->h) / l->data.spriteHeight) / 256;
				pixel = get_pixel_obj(l, l->si, texX, texY);
				if (pixel != l->data.zpixel)
					put_pixel(d->screen, sx, sy, pixel);
				l->data.dst_fromplayer = distance(d->player.x, d->player.y,
					l->x, l->y); 
				d->map.depth_buffer[sx] = l->data.dst_fromplayer;
				sy++;
			}
		}
		sx++;
	}
}

void			objects(t_wolf *data, t_object *list)
{
	t_object	*head;

	head = list;
	if (list == NULL)
		return ;
	while (list)
	{
		list->data.zpixel = get_pixel(data, list->si, 0, 0);
		if (list->type > 2 && list->type < 10)
		{
			list->i = (int)list->x + data->map.width * (int)list->y;
			get_obj_calc(data, list);
			display_object(data, list);
		}
		list = list->next;
	}
	list = head;
}
